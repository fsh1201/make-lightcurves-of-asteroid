#include "sca.h"
#include "cMatrix.h"

double falpha(double alpha)
{
	return fa * exp(-alpha / fd) + fk * alpha + 1;
}

double sca(double mu, double mu0, double alpha)
{
	double sl = mu * mu0;
	double sls = sl / (mu + mu0);
	return falpha(alpha) * (sls + fc * sl);
}

vertex rotate(vertex v, double omg, double t, double lp, double bp)
{
	double** a = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = new double[3];
	}
	double cb = cos(bp);
	double sb = sin(bp);
	a[0][0] = sb;	a[0][1] = 0;	a[0][2] = -cb;
	a[1][0] = 0;	a[1][1] = 1;	a[1][2] = 0;
	a[2][0] = cb;	a[2][1] = 0;	a[2][2] = sb;
	cMatrix bm(a, 3, 3);

	double sl = sin(lp);
	double cl = cos(lp);
	double** b = new double* [3];
	for (int i = 0; i < 3; i++)
	{
		b[i] = new double[3];
	}
	b[0][0] = cl;	b[0][1] = sl;	b[0][2] = 0;
	b[1][0] = -sl;	b[1][1] = cl;	b[1][2] = 0;
	b[2][0] = 0;	b[2][1] = 0;	b[2][2] = 1;
	cMatrix lm(b, 3, 3);

	double phi = omg * t;
	double sp = sin(phi);
	double cp = cos(phi);
	double** c = new double* [3];
	for (int i = 0; i < 3; i++)
	{
		c[i] = new double[3];
	}
	c[0][0] = cp;	c[0][1] = sp;	c[0][2] = 0;
	c[1][0] = -sp;	c[1][1] = cp;	c[1][2] = 0;
	c[2][0] = 0;	c[2][1] = 0;	c[2][2] = 1;
	cMatrix pm(c, 3, 3);

	double* r = new double[3];
	r[0] = v.vx();
	r[1] = v.vy();
	r[2] = v.vz();
	cMatrix rm(r, 3, 1);
	for (int i = 0; i < 3; i++)
	{
		delete[] a[i];
		delete[] b[i];
		delete[] c[i];
	}
	delete[] a;
	delete[] b;
	delete[] c;
	delete[] r;

	cMatrix re = pm * bm * lm * rm;
	vertex v1(re[0][0], re[1][0], re[2][0]);
	return v1;
}