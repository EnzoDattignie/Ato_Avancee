#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int max = 1e9; 

int main() {
    double x = 2;
    for  (int i=0; i < max; i++ ) {
        x = pow(x,2);
        if (x > max) {
            x = 1;
        }
    }
    printf("%f",x);
    return 0;
}