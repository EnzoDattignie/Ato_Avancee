#include <stdio.h> 


int main() {

  const int N=1000;
  
  const int dim=100;
  double a [dim][dim];
  double b [dim][dim];
  
  
  for (int n=0; n<N; n++) {
    
    /* mauvais (en C) : ligne par ligne*/
    for  (int i=0; i<dim; i++){ /*ligne i*/
      for (int j=0; j<dim; j++) { /*colonne j*/
    	b[j][i] = a[j][i];
      }
    }

  }

  printf("a[0] = %lf ",a[0][0] );
  return 0;
}
