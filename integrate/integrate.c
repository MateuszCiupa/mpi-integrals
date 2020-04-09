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

void split_shares(share_t *shares, int world_size, double begin, double end, int num_points) {
    int modulo = num_points % world_size;
    for (int i=0; i<world_size; i++) {
        int equal_share = (num_points - modulo) / world_size;
        int n = equal_share + (i < modulo ? 1 : 0);
        double x = (end-begin) / num_points;
        double b = (i < modulo ? equal_share*i : (equal_share+1)*modulo + (i-modulo)*equal_share) * x;
        double e = b + x*n;
        shares[i] = (share_t){ b, e, n };
    }
}