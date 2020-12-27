#include "facet.h"
facet::facet(vertex v1, vertex v2, vertex v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	vertex x = v2 - v1;
	vertex y = v3 - v2;
	this->n = vertex(x.vy() * y.vz() - x.vz() * y.vy(), x.vz() * y.vx() - x.vx() * y.vz(), x.vx() * y.vy() - x.vy() * y.vx());
	this->area = sqrt(this->n.innerProduct(this->n)) * 0.5;
	this->g = vertex((v1.vx() + v2.vx() + v3.vx()) / 3, (v1.vy() + v2.vy() + v3.vy()) / 3, (v1.vz() + v2.vz() + v3.vz()) / 3);
}

facet::facet(const facet& f)
{
	this->v1 = f.v1;
	this->v2 = f.v2;
	this->v3 = f.v3;
	this->n = f.n;
	this->g = f.g;
	this->area = f.area;
}

void facet::operator=(facet f)
{
	this->v1 = f.v1;
	this->v2 = f.v2;
	this->v3 = f.v3;
	this->n = f.n;
	this->g = f.g;
	this->area = f.area;
}

double facet::angleNV(vertex v)
{
	return this->n.angle(v);
}

double facet::angleFF(facet f)
{
	return this->n.angle(f.n);
}