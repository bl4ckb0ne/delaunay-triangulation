#include "triangle.h"

Triangle::Triangle(const VertexType &_p1, const VertexType &_p2, const VertexType &_p3) :
	p1(_p1), p2(_p2), p3(_p3), e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), isBad(false)
{}

bool
Triangle::containsVertex(const VertexType &v) const
{
	// return p1 == v || p2 == v || p3 == v;
	return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v);
}

bool
Triangle::circumCircleContains(const VertexType &v) const
{
	const double ab = p1.norm2();
	const double cd = p2.norm2();
	const double ef = p3.norm2();

	const double circum_x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) / (p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y));
	const double circum_y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) / (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x));

	const VertexType circum(half(circum_x), half(circum_y));
	const double circum_radius = p1.dist2(circum);
	const double dist = v.dist2(circum);
	return dist <= circum_radius;
}

bool
Triangle::operator ==(const Triangle &t)
{
	return	(this->p1 == t.p1 || this->p1 == t.p2 || this->p1 == t.p3) &&
			(this->p2 == t.p1 || this->p2 == t.p2 || this->p2 == t.p3) &&
			(this->p3 == t.p1 || this->p3 == t.p2 || this->p3 == t.p3);
}

std::ostream&
operator <<(std::ostream &str, const Triangle &t)
{
	return str << "Triangle:" << "\n\t" <<
			t.e1 << "\n\t" <<
			t.e2 << "\n\t" <<
			t.e3 << '\n';
}

bool almost_equal(const Triangle &t1, const Triangle &t2)
{
	return	(almost_equal(t1.p1 , t2.p1) || almost_equal(t1.p1 , t2.p2) || almost_equal(t1.p1 , t2.p3)) &&
			(almost_equal(t1.p2 , t2.p1) || almost_equal(t1.p2 , t2.p2) || almost_equal(t1.p2 , t2.p3)) &&
			(almost_equal(t1.p3 , t2.p1) || almost_equal(t1.p3 , t2.p2) || almost_equal(t1.p3 , t2.p3));
}
