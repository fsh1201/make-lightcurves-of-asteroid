#ifndef SCAH
#define SCAH

#include "facet.h"
const double fa = 0.5;
const double fd = 0.1;
const double fk = -0.5;
const double fc = 0.1;

double falpha(double alpha);

double sca(double mu, double mu0, double alpha);

vertex rotate(vertex v, double omg, double t, double lp, double bp);

#endif