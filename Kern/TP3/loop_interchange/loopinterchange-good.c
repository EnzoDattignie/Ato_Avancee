#include <stdio.h> 


int main(int argc, char *argv[]) {
  long double n = 10000;
  long double n2 = 100;
  if (argc == 3) {
      sscanf(argv[1],"%Lf",&n);
      sscanf(argv[2],"%Lf",&n2);
  }
  long int N=(long)n;
  long int dim=(long)n2;
  double a [dim][dim];
  double b [dim][dim];
  
  
  for (int n=0; n<N; n++) {
    
    /* bon (en C) : colonne par colonne*/
    for  (int i=0; i<dim; i++){ /*colonne i*/
      for (int j=0; j<dim; j++) { /*ligne j*/
    	b[i][j] = a[i][j];
      }
    }

  }

  printf("a[0] = %lf ",a[0][0] );
  return 0;
}
