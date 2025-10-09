// vectorisation-loops-check.c

/* 
README : illustrate caveats when trying to vectorise loops
 compile/run as gcc -O3 -fopt-info-vec -fopt-info-vec-missed vectorisation-loops-check.c  && time ./a.out  
*/

#include <stdio.h>
#include <assert.h>

int f(int i,int imax) {
  return (i<imax)*27;
}
    
#define dim 100000
int x[dim];
int y[dim];
int temp[dim];


int main() {

  // const int dim=100000;
  // int x[dim];
  // int y[dim];
  
  // loop #0: Sortir les variables du main ??? Et changer dim en define
  for (int i=0; i<dim; i++)
    x[i]=dim-i-1;
  
  // loop #1: Same as 0
  for (int i=0; i<dim; i++)
    x[i] *=i;
  
  // loop #2: Same as 0
  const int k=10;
  assert(k>=0);
  assert(k<dim/2);
  for (int i=dim/2; i<dim; i++)
    x[i]=x[i-2]; // dummy operation
  
  // loop #3:
  for (int i=0; f(i,dim)>0; i++)
    x[i]+=2;  

  // // loop #4: Non vectorisable du au controle if
  // for (int i=0; i<dim; i++) {
  //   if (i>0) //erreur ??
  //     x[i]+=2;
  // }

  //loop #4 vectorisable
  for (int i=1; i<dim; i++) {
      x[i]+=2;
  }

  // loop #5: 
  for (int i=0; i<dim; i++)
    x[i]+=f(x[i],dim);  

  // loop #5: 
  for (int i=0; i<dim; i++)
    x[i]+=y[i];  


//   // loop #6: Ici il refuse car il a peur que x[y[i]] soit modifié avant d'etre exécuté. Par conséquent on peut utiliser une mémoire tampon, mais selon les listes cela pourrait etre faux par exemple si x[i] est un array linéaire et que y[i] est nul pour tout i, x[0] sera doublé puis ensuite ajouté a chaque x[i] i>0
//   for (int i=0; i<dim; i++) {
//     x[i]+=x[y[i]];  
// }

//  // loop #6: piste de vectorisation pas tout a fait juste
  for (int i=0; i<dim; i++) {
    temp[i] = x[y[i]];  
  }
  for (int i=0; i<dim; i++) {
    x[i] += temp[i];  
  }
  // printf("k: %d",k); // dummy print
}
