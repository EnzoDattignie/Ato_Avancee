#include <stdio.h>

int main(int argc, char *argv[]) {
    long double n = 10000;
    long double n2 = 100;
    if (argc == 3) {
        sscanf(argv[1],"%Lf",&n);
        sscanf(argv[2],"%Lf",&n2);
    }
    const long niter = (long)n;
    long int ndim=n2;

    int a[ndim], b[ndim];

    for (long int n=0; n<niter; n++) {

        long int i;
        
        for (i=0; i<ndim; i++) {
            a[i]=1;                     
            b[i]=2;
            }
        }
    printf("%d", b[0]);
   return 0;
}


