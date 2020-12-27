#include <fstream>
#include "facet.h"
#include "sca.h"
#include "cMatrix.h"
#include "j.h"

const double pi = 3.14159265358979323846264338327950288419716;
const double Tspin = 7.3 /24;	//��ת����
const double lp = 120 * pi / 180;	//��ת��ָ��lambda
const double bp = 50 * pi / 180;	//��ת��ָ��beta
const double omg = 2 * pi / Tspin;	//��ת���ٶ�

const double Te = 365.0;	//����ת����
const double Ta = 5 * Te;	//С���ǹ�ת����
const double omga = 2 * pi / Ta;	//����ת���ٶ�
const double omge = 2 * pi / Te;	//С���ǹ�ת���ٶ�

const double ts = 2456531.2;	//�۲⿪ʼʱ��
const double dt = 0.01 * Tspin;	//�������
const double te = ts + 5.0 * 365.0;	//�۲����ʱ��
const double tob = 350.0;	//���ȼ��
const double tin = 3.0;	//�۲⼾���ڼ��
const double tl = 6.0 / 24.0;	//ÿ�ι۲�ʱ��
const double tg = 30.0;	//����ʱ��

const double inc = 15 * pi / 180;	//С���ǹ�����

using namespace std;

int main()
{
	/*ifstream shape("D:\\wuli\\damit\\files\\asteroid_103\\model_104\\shape.txt");
	ofstream lc("D:\\nlc.txt");
	int nFacet = 0;
	int nVertex = 0;
	shape >> nVertex;
	shape >> nFacet;
	
	vertex* ver = new vertex[nVertex];
	facet* fac = new facet[nFacet];
	for (int i = 0; i < nVertex; i++)
	{
		double tx, ty, tz;
		shape >> tx;
		shape >> ty;
		shape >> tz;
		ver[i] = vertex(tx, ty, tz);
	}

	for (int i = 0; i < nFacet; i++)
	{
		int t1, t2, t3;
		shape >> t1;
		shape >> t2;
		shape >> t3;
		fac[i] = facet(ver[t1 - 1], ver[t2 - 1], ver[t3 - 1]);
	}

	vector<vector<double>> time;
	vector<vector<vertex>> vers;
	vector<vector<vertex>> vere;
	for (double t1 = ts; t1 < te; t1 = t1 + tob)
	{
		for (double t2 = t1; t2 < t1 + tg; t2 = t2 + tin)
		{
			vector<double> ttemp1;
			vector<vertex> vstemp1;
			vector<vertex> vetemp1;
			for (double t = t2; t < t2 + tl; t = t + dt)
			{
				ttemp1.push_back(t);
				double xe = cos(omge * t);
				double ye = sin(omge * t);
				double ze = 0;
				double xa = 3 * cos(omge * t);
				double ya = 3 * sin(omge * t) * cos(inc);
				double za = -3 * sin(omge * t) * sin(inc);
				vstemp1.push_back(vertex(-xa, -ya, -za));
				vetemp1.push_back(vertex(xe - xa, ye - ya, ze - za));
			}
			time.push_back(ttemp1);
			vers.push_back(vstemp1);
			vere.push_back(vetemp1);
			ttemp1.clear();
			vstemp1.clear();
			vetemp1.clear();
		}
	}

	lc.precision(14);
	cout.precision(14);
	vector<double> bright;
	lc << time.size() << endl;
	for (int i = 0; i < time.size(); i++)
	{
		lc << time[i].size() << " " << 0 << endl;
		for (int k = 0; k < time[i].size(); k++)
		{
			vertex vs = rotate(vers[i][k], omg, time[i][k], lp, bp);
			vertex ve = rotate(vere[i][k], omg, time[i][k], lp, bp);
			double alpha = vs.angle(ve);
			double b = 0;
			for (int j = 0; j < nFacet; j++)
			{
				double m = fac[j].fn().innerProduct(ve);
				double m0 = fac[j].fn().innerProduct(vs);
				double mu = cos(fac[j].angleNV(ve));
				double mu0 = cos(fac[j].angleNV(vs));
				if (m > 0 && m0 > 0)
				{
					b = b + fac[j].a() * sca(mu, mu0, alpha);
				}
			}
			bright.push_back(b);
			lc << time[i][k] << " " << b << " " << vers[i][k] << " " << vere[i][k] << endl;
		}
	}*/

	ofstream U("D:\\u.txt");
	vector<double> t;
	double T = 10.0 * 3600.0;
	double C = 680.0;
	double K = 2.0;
	double p = 2.5e3;
	double a = K / p / C;
	double lskin = sqrt(K / p / C / (2 * pi / T));
	double d = 8.0 * lskin;
	d = 2.0;
	double ht = 10;
	double hx = 0.1;
	double r = a * ht / hx / hx;
	double n3 = 6, n4 = 24;
	double epsi = 0.94;
	double sig = 5.67e-8;
	for (double i = 0; i < 10 * T; i = i + ht)
	{
		t.push_back(i);
	}
	vector<double> x;
	for (double i = 0; i < d; i = i + hx)
	{
		x.push_back(i);
	}
	double** u = new double* [t.size()];
	for (int i = 0; i < t.size(); i++)
	{
		u[i] = new double[x.size()];
	}
	for (int i = 0; i < x.size(); i++)
	{
		u[0][i] = 160.0;
	}
	for (int n = 1; n < t.size(); n++)
	{
		for (int j = 1; j < x.size() - 1; j++)
		{
			u[n][j] = r * (u[n-1][j + 1] + u[n-1][j - 1]) + (1 - 2*r) * u[n-1][j];
		}
		double u1 = (3 * epsi * sig * pow(u[n][1], 4) + K / hx * u[n][1] + 1367 / 9 * Sh(2 * pi / T, t[n])) / (4 * epsi * sig * pow(u[n][1], 3) + K / hx);
		//double u1 = (3 * epsi * sig * pow(160.0, 4) + K / hx * 160.0 + 1373 / 9 * Sh(2 * pi / T, t[n])) / (4 * epsi * sig * pow(160.0, 3) + K / hx);
		double u2 = (3 * epsi * sig * pow(u[n - 1][0], 4) + K / hx * u[n - 1][0] + 1373 / 9 * Sh(2 * pi / T, t[n])) / (4 * epsi * sig * pow(u[n - 1][0], 3) + K / hx);
		u[n][0] = u1;
		u[n][x.size() - 1] = u[n][x.size() - 2];
	}
	U.precision(10);
	for (int i = 0; i < x.size(); i++)
	{
		U << x[i] << " ";
	}
	U << endl;
	for (int i = 0; i < t.size(); i++)
	{
		if (i % 60 == 0)
		{
			U << t[i] << " ";
			for (int j = 0; j < x.size(); j++)
			{
				U << u[i][j] << " ";
			}
			U << endl;
		}
	}
	U.close();
	return 0;
}