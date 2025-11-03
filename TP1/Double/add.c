#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    long double n = 1;
    if (argc == 2) {
        sscanf(argv[1],"%Lf",&n);
    }
    const long N = (long)n;
    double x = 3;
    for (long i = 0;i<N ;i++) {
        x = x+3;
        // x = x*2;
        // x = x/0.5;
        if (x > 1e6) {
            x = 3;
        }
    }
    printf("x = %f\n",x);
    return 0;
}

