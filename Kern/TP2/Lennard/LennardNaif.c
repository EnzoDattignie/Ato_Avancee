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
        double r = sqrt(pow(dx,2)+pow(dy,2));
        double u = 4*(1/pow(r,12) - 1/pow(r,6));
        double fr = 4*(12/pow(r,13) - 6/pow(r,7));
        double cos =  dx/r;
        double sin = dy/r;
        *u12 = *u12+u;
        *f12x = *f12x+fr*cos;
        *f12y = *f12y+fr*sin;
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