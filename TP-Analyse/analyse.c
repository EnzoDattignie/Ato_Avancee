#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//On vaa commencer par mesurer la fonction de distribution radiale pour une seule config.

void read_file (FILE *fp, int **nSO, int *ndim, double **pos) {
    int i, n, err, nO=0, nS=1;
    double x, y, z;
    char a[1];
    err = fscanf(fp,"%d",&n);
    char buffer[25];
    err = fscanf(fp, "%s %lf %lf %lf", a, &x, &y, &z);
    err = fscanf(fp, "%s %lf %lf %lf", a, &x, &y, &z);
    (*nSO)[0] = n;
    *ndim = 3;
    *pos = malloc((*ndim)*n*sizeof(double));
    for (i=0; i<n; i++) {
        err = fscanf(fp, "%s %lf %lf %lf", a, &x, &y, &z);
        //printf("x %f, y %f, z %f\n",x,y,z);
      (*pos)[i*(*ndim)]   = x;
      (*pos)[i*(*ndim)+1] = y;
      (*pos)[i*(*ndim)+2] = z;
      if (a[0] == 'S') {
        nS++;
      } else if (a[0] == 'O') {
        nO++;
     }
    }
    (*nSO)[1] = nS;
    (*nSO)[2] = nO;
  }

int main (int argc, char * argv[]) {
    int ndim = 3,*nSO;
    double *box, *pos;
    FILE *file, *log;
    int *Liste;
    file = fopen("test.xyz","r");
    log  = fopen("res/Test.log","w");

    nSO = malloc(3*sizeof(nSO));

    read_file(file,&nSO,&ndim,&pos);
    for (int i = 0; i < nSO[0]; i++) {
        printf("x : %f, y : %f, z : %f\n")
    }

}