#include "vertex.h"
double vertex::innerProduct(vertex n)
{
	return this->x * n.x + this->y * n.y + this->z * n.z;
}
vertex vertex::rn()
{
	vertex v;
	v.x = this->x / this->r;
	v.y = this->y / this->r;
	v.z = this->z / this->r;
	return v;
}

vertex vertex::crossProduct(vertex n)
{
	double i = y * n.vz() - n.vy() * z;
	double j = n.vx() * z - x * n.vz();
	double k = x * n.vy() - n.vx() * y;
	vertex v(i, j, k);
	return v;
}

double vertex::angle(vertex n)
{
	return acos(this->rn().innerProduct(n.rn()));
}
