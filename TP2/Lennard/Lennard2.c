#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    long double n = 1;
    if (argc == 2) {
        sscanf(argv[1],"%Lf",&n);
    }
    const long N = (long)n;
    const double Rc = 2.5;
    
    int interactions (double x1, double y1, double x2, double y2, double *u12, double *f12x, double *f12y) {
        double dx = x2-x1;
        double dy = y2-y1;
        double r2 = dx*dx+dy*dy;
        double r6 = r2*r2*r2;
        double r12 = r6*r6;
        double u = 4*(1/r12 - 1/r6);
        double fr = 4*(12/(r12*r2) - 6/(r6*r2));
        *u12 = *u12+u;
        *f12x = *f12x+fr*dx;
        *f12y = *f12y+fr*dy;
        return 0;
    }

    double x1 = 0;
    double y1 = 0;
    double x2 = 1;
    double y2 = 1;
    double u12 = 0;
    double f12x = 0;
    double f12y = 0;

    for (long i = 0; i < N;i++) {
        interactions(x1,y1,x2,y2,&u12,&f12x,&f12y);
    }
    printf("u : %f, Fx : %f, Fy : %f\n",u12,f12x,f12y);



    return 0;
}