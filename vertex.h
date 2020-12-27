#ifndef VERTEXH
#define VERTEXH

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class vertex
{
private:
	double x;
	double y;
	double z;
	double r;
public:
	vertex(double*a):x(a[0]),y(a[1]),z(a[2]),r(sqrt(x*x+y*y+z*z)){}
	vertex(double x,double y,double z):x(x),y(y),z(z),r(sqrt(x* x + y * y + z * z)) {}
	vertex(const vertex& n):vertex(n.x,n.y,n.z){}
	vertex():vertex(0,0,0){}
	vertex operator+(vertex n)
	{
		vertex v(this->x + n.x, this->y + n.y, this->z + n.z);
		return v;
	}
	vertex operator-(vertex n)
	{
		vertex v(this->x - n.x, this->y - n.y, this->z - n.z);
		return v;
	}
	void operator=(vertex n)
	{
		this->x = n.x;
		this->y = n.y;
		this->z = n.z;
		this->r = n.r;
	}
	double innerProduct(vertex n);
	vertex crossProduct(vertex n);
	vertex rn();
	double angle(vertex n);
	double vx() { return this->x; }
	double vy() { return this->y; }
	double vz() { return this->z; }
	double vr() { return this->r; }
	friend ostream& operator<<(ostream& out, const vertex& v)
	{
		out << v.x << " " << v.y << " " << v.z;
		return out;
	}
};

#endif //VERTEXH