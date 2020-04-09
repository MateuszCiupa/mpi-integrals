#include "integrate.h"

double integrate(double (*func)(double), double begin, double end, int num_points) {
    double result = 0;
    for (int i=1; i<=num_points; i++) 
        result += func(begin+i*(end-begin)/num_points) * (end-begin)/num_points;
    return result;
}

double fun(double x) {
    return x*x;
}