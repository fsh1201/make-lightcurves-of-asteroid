#ifndef FACETH
#define FACETH
#include "vertex.h"
class facet
{
private:
	vertex v1;	//顶点1
	vertex v2;	//顶点2
	vertex v3;	//顶点3
	double area;	//面积
	vertex n;	//法向量
	vertex g;	//中心
public:
	facet(vertex v1, vertex v2, vertex v3);
	facet(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3):facet(vertex(x1,y1,z1),vertex(x2,y2,z2),vertex(x3,y3,z3)){}
	facet(const facet& f);
	facet():facet(0,0,0,0,0,0,0,0,0){}
	void operator=(facet f);
	double angleNV(vertex v);
	double angleFF(facet f);
	friend ostream& operator<<(ostream& out, const facet& f)
	{
		out << f.v1 << endl << f.v2 << endl << f.v3 << endl;
		return out;
	}
	vertex fn() { return n; }
	vertex fg() { return g; }
	double a() { return area; }
	vertex fv1() { return v1; }
	vertex fv2() { return v2; }
	vertex fv3() { return v3; }
};

#endif //FACETH