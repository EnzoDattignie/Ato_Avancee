#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

int main() {
    double dx = 1.3413432;
    double dy = 1.6598751;
    double r2 = dx*dx+dy*dy;
    double r = sqrt(r2);
    printf("%f,%f",r2,r*r);
}