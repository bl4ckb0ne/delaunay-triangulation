#include "triangle.h"

namespace dt {

template<typename T>
Triangle<T>::Triangle(const VertexType &v1, const VertexType &v2, const VertexType &v3) :
	a(&v1), b(&v2), c(&v3), isBad(false)
{}

template<typename T>
bool
Triangle<T>::containsVertex(const VertexType &v) const
{
	// return p1 == v || p2 == v || p3 == v;
	return almost_equal(*a, v) || almost_equal(*b, v) || almost_equal(*c, v);
}

template<typename T>
bool
Triangle<T>::circumCircleContains(const VertexType &v) const
{
	const T ab = a->norm2();
	const T cd = b->norm2();
	const T ef = c->norm2();

	const T ax = a->x;
	const T ay = a->y;
	const T bx = b->x;
	const T by = b->y;
	const T cx = c->x;
	const T cy = c->y;

	const T circum_x = (ab * (cy - by) + cd * (ay - cy) + ef * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
	const T circum_y = (ab * (cx - bx) + cd * (ax - cx) + ef * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

	const VertexType circum(half(circum_x), half(circum_y));
	const T circum_radius = a->dist2(circum);
	const T dist = v.dist2(circum);
	return dist <= circum_radius;
}

template<typename T>
bool
Triangle<T>::operator ==(const Triangle &t) const
{
	return	(*this->a == *t.a || *this->a == *t.b || *this->a == *t.c) &&
			(*this->b == *t.a || *this->b == *t.b || *this->b == *t.c) &&
			(*this->c == *t.a || *this->c == *t.b || *this->c == *t.c);
}

template<typename U>
std::ostream&
operator <<(std::ostream &str, const Triangle<U> &t)
{
	return str << "Triangle:" << "\n\t" <<
			*t.a << "\n\t" <<
			*t.b << "\n\t" <<
			*t.c << '\n';
}

template struct Triangle<float>;
template struct Triangle<double>;

} // namespace dt
