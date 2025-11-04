// vectorisation-loops-check.c

/* 
README : vectorise a non-vectorisable loop via a temporary array with re-indexing

compile/run as gcc -O3 -fopt-info-vec -fopt-info-vec-missed vectorisation-reindexation.c  && time ./a.out  
 */

#include <stdio.h>
#include <assert.h>

#define dim 10000000
int A[dim];
int temp[dim];

int main() {	  

  // initialise array
  for (int i=0; i<dim; i++)
    A[i] = (i+1);

    for (int i=0; i<dim; i++) {
      temp[i] = A[dim-i-1];}
  // calculate required sum
  int S=0;
  for (int i=0; i<dim; i++) {
    S += (i+1)*A[i]; 
  }
  for (int i=0; i<dim; i++) {
    S += i*temp[i];}

  printf("S: %d",S); // dummy print
}
