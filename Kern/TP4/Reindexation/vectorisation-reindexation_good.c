// vectorisation-loops-check.c

/* 
README : vectorise a non-vectorisable loop via a temporary array with re-indexing

compile/run as gcc -O3 -fopt-info-vec -fopt-info-vec-missed vectorisation-reindexation.c  && time ./a.out  
 */

#include <stdio.h>
#include <assert.h>
#define dim 1000000

int main() {	  

  static double A[dim];
  static double B[dim];
  
  // initialise array
  for (int i=0; i<dim; i++)
    A[i] = 1./(i+1);

  for (int i=0; i<dim; i++)
    B[i] = A[dim-i-1];

  // calculate required sum
  double S=0;
  for (int i=0; i<dim; i++)
    S += (i+1)*A[i] +1./(i+1)*B[i]; 
  

  printf("S: %lf",S); // dummy print
}
