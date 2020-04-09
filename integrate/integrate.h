#ifndef INTEGRATE_H_
#define INTEGRATE_H

typedef struct {
    double b;
    double e;
    int n;
} share_t;

double integrate(double (*func)(double), double begin, double end, int num_points);
double fun(double x);
void split_shares(share_t *shares, int world_size, double begin, double end, int num_points);

#endif