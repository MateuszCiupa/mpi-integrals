#ifndef INTEGRATE_H_
#define INTEGRATE_H

double integrate(double (*func)(double), double begin, double end, int num_points);
double fun(double x);

#endif