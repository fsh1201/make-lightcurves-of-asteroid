#ifndef CMATRIXH
#define CMATRIXH

#include <iostream>
#include <vector>
#include "vertex.h"
using namespace std;

class cMatrix
{
private:
	double** a;
	int m;
	int n;
public:
	cMatrix(double** a, int m, int n);
	cMatrix(double* l, int m, int n);
	cMatrix();
	cMatrix(const cMatrix& p);
	cMatrix(cMatrix&& p);
	~cMatrix()
	{
		if (this->a)
		{
			for (int i = 0; i < m; i++)
			{
				delete[] this->a[i];
			}
			delete[] this->a;
		}
	}

	vector<double> operator[](int k)
	{
		return vector<double>(this->a[k], this->a[k] + n);
	}

	cMatrix operator+(cMatrix p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] + p.a[i][j];
			}
		}
		return m1;
	}

	cMatrix operator+(double p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] + p;
			}
		}
		return m1;
	}

	cMatrix operator-(cMatrix p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] - p.a[i][j];
			}
		}
		return m1;
	}

	cMatrix operator-(double p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] - p;
			}
		}
		return m1;
	}

	cMatrix operator/(cMatrix p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] / p.a[i][j];
			}
		}
		return m1;
	}

	cMatrix operator/(double p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] / p;
			}
		}
		return m1;
	}

	cMatrix operator*(cMatrix p)
	{
		if (this->n != p.m)
		{
			cout << "矩阵无法相乘" << endl;
			exit(-1);
		}
		cMatrix m1;
		m1.m = this->m;
		m1.n = p.n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < p.n; j++)
			{
				m1.a[i][j] = 0;
				for (int k = 0; k < n; k++)
				{
					m1.a[i][j] += this->a[i][k] * p.a[k][j];
				}
			}
		}
		return m1;
	}

	cMatrix operator*(double p)
	{
		cMatrix m1;
		m1.m = this->m;
		m1.n = this->n;
		m1.a = new double* [m1.m];
		for (int i = 0; i < m1.m; i++)
		{
			m1.a[i] = new double[m1.n];
			for (int j = 0; j < m1.n; j++)
			{
				m1.a[i][j] = this->a[i][j] * p;
			}
		}
		return m1;
	}

	vertex operator*(vertex p)
	{
		if (this->m < 3)
		{
			cout << "无法相乘" << endl;
			exit(-5);
		}
		double x = a[0][0] * p.vx() + a[0][1] * p.vy() + a[0][2] * p.vz();
		double y = a[1][0] * p.vx() + a[1][1] * p.vy() + a[1][2] * p.vz();
		double z = a[2][0] * p.vx() + a[2][1] * p.vy() + a[2][2] * p.vz();
		vertex v(x, y, z);
		return v;
	}

	vector<double> operator*(vector<double> p)
	{
		if (m < p.size())
		{
			cout << "无法相乘" << endl;
			exit(-6);
		}
		vector<double> v(p.size());
		for (int i = 0; i < p.size(); i++)
		{
			v[i] = 0;
			for (int j = 0; j < p.size(); j++)
			{
				v[i] += a[i][j] * p[j];
			}
		}
		return v;
	}

	void operator=(cMatrix p)
	{
		if (this->a)
		{
			for (int i = 0; i < this->m; i++)
			{
				delete[] this->a[i];
			}
			delete[] this->a;
		}
		m = p.m;
		n = p.n;
		a = new double* [m];
		for (int i = 0; i < m; i++)
		{
			a[i] = new double[n];
			for (int j = 0; j < n; j++)
			{
				a[i][j] = p.a[i][j];
			}
		}
	}

	double det();
	cMatrix I();
	cMatrix T();

	friend ostream& operator<<(ostream& out, const cMatrix& c)
	{
		for (int i = 0; i < c.m; i++)
		{
			for (int j = 0; j < c.n; j++)
			{
				out << c.a[i][j] << " ";
			}
			out << endl;
		}
		return out;
	}
};

#endif // !CMATRIX