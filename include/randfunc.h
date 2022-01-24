#ifndef RANDFUNC_H
#define RANDFUNC_H

double DoubleRandValue(double lower, double upper);
double RandProbability();
int IntRandValue(int range);
double FindMax(double x, double y);
double FindMin(double x, double y);

double DoubleRandValue(double lower, double upper) {
  double value;
  value = ((double)rand() / ((double)RAND_MAX + 1.0)) * (upper - lower) + lower;
  return value;
}

double RandProbability() {
  double value;
  value = (double)rand() / ((double)RAND_MAX + 1.0);
  return value;
}

int IntRandValue(int range) {
  int value;
  value = rand() % range;
  return value;
}

double FindMax(double x, double y) {
  double max;
  if (x > y) {
    max = x;
  } else {
    max = y;
  }
  return max;
}

double FindMin(double x, double y) {
  double min;
  if (x < y) {
    min = x;
  } else {
    min = y;
  }
  return min;
}

#endif