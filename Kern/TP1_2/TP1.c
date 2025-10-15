#include <stdio.h>
#include <stdlib.h>

#define N (10*100000000) //La valeur de N est très grande pour permettre d'obtenir un temps mesurable, on la fera varier de 1e8 a 9e8 pour mesurer la différence par la suite

int main() {
    int x = 3;

    for (int i = 0;i<N ;i++) { 
        if (x > 10000000) { //Quand x deviens trop grand on le réinitialise pour éviter un quelconque bug du compilateur
            x = 3;
        }
        // Ligne suivante a décommenter pour l'addition
        x = x+3; 

        // Ligne suivante a décommenter pour la multiplication
        // x = x*2;

        // Ligne suivante a décommenter pour la division
        // x = x/0.5; 
    }
    // printf("x = %f\n",x);
    printf("x = %i\n",x); //selon si on agis sur des flotants ou des doubles
    return 0;
}