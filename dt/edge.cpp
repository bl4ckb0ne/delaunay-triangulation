#include "edge.h"

Edge::Edge(const VertexType &_p1, const VertexType &_p2) :
	p1(_p1), p2(_p2)
{}

bool
Edge::operator ==(const Edge &e)
{
	return (this->p1 == e.p1 && this->p2 == e.p2) ||
			(this->p1 == e.p2 && this->p2 == e.p1);
}

std::ostream&
operator <<(std::ostream &str, const Edge &e)
{
	return str << "Edge " << e.p1 << ", " << e.p2;
}

bool almost_equal(const Edge &e1, const Edge &e2)
{
	return	(almost_equal(e1.p1, e2.p1) && almost_equal(e1.p2, e2.p2)) ||
			(almost_equal(e1.p1, e2.p2) && almost_equal(e1.p2, e2.p1));
}
