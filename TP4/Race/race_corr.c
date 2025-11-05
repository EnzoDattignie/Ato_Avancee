// race.c : illustrate race condition in OpenMP
/* 
compilation:  gcc -fopenmp race.c 
*/

#include <stdio.h>
#include "omp.h"



void main() {

  int Liste[10];
  for (int i = 0;i < 10;i++) {
    Liste[i]=0;
  }
  int A = 0;
  omp_set_num_threads(5);

#pragma omp parallel
  {
    int ID = omp_get_thread_num();
    Liste[ID] += 1;

    printf("ID : %d\n",ID);
    }

  
  for (int i = 0;i < 10;i++) {
    A += Liste[i]*i;
  }

  printf("A:  %d (expected: 10)\n",A);
}
