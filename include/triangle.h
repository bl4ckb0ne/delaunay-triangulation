#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "numeric.h"
#include "vector2.h"
#include "edge.h"

template<typename T>
struct Triangle
{
	using Type = T;
	using VertexType = Vector2<Type>;
	using EdgeType = Edge<Type>;

	Triangle() = default;
	Triangle(const Triangle&) = default;
	Triangle(Triangle&&) = default;
	Triangle(const VertexType &v1, const VertexType &v2, const VertexType &v3);

	bool containsVertex(const VertexType &v) const;
	bool circumCircleContains(const VertexType &v) const;

	Triangle &operator=(const Triangle&) = default;
	Triangle &operator=(Triangle&&) = default;
	bool operator ==(const Triangle &t) const;

	template<typename U>
	friend std::ostream &operator <<(std::ostream &str, const Triangle<U> &t);

	const VertexType *a;
	const VertexType *b;
	const VertexType *c;
	bool isBad = false;

	static_assert(std::is_floating_point_v<Triangle<T>::Type>,
		"Type must be floating-point");
};

template<typename T>
bool almost_equal(const Triangle<T> &t1, const Triangle<T> &t2)
{
	return	(almost_equal(*t1.a , *t2.a) || almost_equal(*t1.a , *t2.b) || almost_equal(*t1.a , *t2.c)) &&
			(almost_equal(*t1.b , *t2.a) || almost_equal(*t1.b , *t2.b) || almost_equal(*t1.b , *t2.c)) &&
			(almost_equal(*t1.c , *t2.a) || almost_equal(*t1.c , *t2.b) || almost_equal(*t1.c , *t2.c));
}

#endif
