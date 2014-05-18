#ifndef RAND_H
#define RAND_H 1
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RAND 2147483647

double rnd();
int RAND(const int & k);
void time_seed();
double mid_rand(const double & ,const double & );
double rnd_flp(const double & );
#endif
