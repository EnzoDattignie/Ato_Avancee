#include <stdio.h>
#include <stdlib.h>

const int max = 1e9; 

int main() {
    double x = 1;
    for  (int i=0; i < max; i++ ) {
        x = x+3;
        if (x > max) {
            x = 1;
        }
    }
    printf("%f",x);
    return 0;
}