#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    long double n = 1;
    if (argc == 2) {
        sscanf(argv[1],"%Lf",&n);
    }
    const long N = (long)n;
    double x = 2e9;
    for (long i = 0;i<N ;i++) {
        x = sqrt(200);
        // x = x*2;
        // x = x/0.5;
        if (x < 2) {
            x = 2e9;
        }
    }
    printf("x = %f\n",x);
    return 0;
}

