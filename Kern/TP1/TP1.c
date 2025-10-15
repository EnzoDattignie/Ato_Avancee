#include <stdio.h>
#include <stdlib.h>

#define N (10*100000000)

int main() {
    int x = 3;
    for (int i = 0;i<N ;i++) {
        x = x+3;
        // x = x*1.01;
        // x = x/0.99;
    }
    printf("x = %i\n",x);
    return 0;
}

