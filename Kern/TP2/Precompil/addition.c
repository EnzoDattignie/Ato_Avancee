#include <stdio.h>
#include <stdlib.h>

const int max = 1e9; 

int main() {
    double x = 1;
    for  (int i=0; i < max; i++ ) {
        x = x+3;
        // x = x/0.5;
        // x = x*2;z
        // x = pow(x,2);
        if (x > max) { //Cette condition permet d'éviter que notre résultat devienne trop grand durant certaines opérations, mais également permet d'éviter les stratégies du compilateur pour éviter d'éxécuter la boucle entiere
            x = 1;
        }
    }
    printf("%f",x);
    return 0;
}