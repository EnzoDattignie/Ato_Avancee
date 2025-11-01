#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    double n = 10*100000000;
    if (argc == 2) {
        sscanf(argv[1],"%lf",&n);
    }
    const int N = (int)n;
    int x = 3;
    for (int i = 0;i<N ;i++) {
        // x = x+3;
        x = x*2;
        // x = x/0.5;
        if (x > 1e6) {
            x = 3;
        }
    }
    printf("x = %i\n",x);
    return 0;
}

