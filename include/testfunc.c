#include <math.h>

#include ".\testfunc.h"

double Test_Function_1(double x1, double x2) {
    double result = 1 + 2 - (cos(2 * PI * x1) - 0.01 * sqrt(x1) + cos(2 * PI * x2) - 0.01 * sqrt(x2));
    return result;
}