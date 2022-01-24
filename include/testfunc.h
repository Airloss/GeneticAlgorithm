#ifndef TESTFUNC_H
#define TESTFUNC_H

#define PI acos(-1.0)

double Test_Function_1(double x1, double x2);
double Test_Function_1(double x1, double x2) {
    double result = 1 + 2 - (cos(2 * PI * x1) - 0.01 * sqrt(x1) + cos(2 * PI * x2) - 0.01 * sqrt(x2));
    return result;
}

#endif