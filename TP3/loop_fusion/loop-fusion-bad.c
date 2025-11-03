#include <stdio.h>

int main(int argc, char *argv[]) {
    long double n = 10000;
    long double n2 = 100000;
    if (argc == 3) {
        sscanf(argv[1],"%Lf",&n);
        sscanf(argv[2],"%Lf",&n2);
    }
    const long N = (long)n;
    long int ndim=n;
    long int niter=n2;
 
    int a[ndim], b[ndim];

    for (long int n=0; n<niter; n++) {

        long int i;
        
        for (i=0; i<ndim; i++)
            a[i]=1;                     

        for (i=0; i<ndim; i++)
            b[i]=2;
    }
    printf("%d", b[0]);
   return 0;
}


