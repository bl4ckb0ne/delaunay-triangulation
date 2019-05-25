#include "edge.h"

Edge::Edge(const VertexType &v1, const VertexType &v2) :
	v(&v1), w(&v2)
{}

bool
Edge::operator ==(const Edge &e) const
{
	return (*(this->v) == *e.v && *(this->w) == *e.w) ||
			(*(this->v) == *e.w && *(this->w) == *e.v);
}

std::ostream&
operator <<(std::ostream &str, const Edge &e)
{
	return str << "Edge " << *e.v << ", " << *e.w;
}

bool almost_equal(const Edge &e1, const Edge &e2)
{
	return	(almost_equal(*e1.v, *e2.v) && almost_equal(*e1.w, *e2.w)) ||
			(almost_equal(*e1.v, *e2.w) && almost_equal(*e1.w, *e2.v));
}
