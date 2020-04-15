#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

template<typename T>
struct Edge
{
	using Type = T;
	using VertexType = Vector2<Type>;

	Edge() = default;
	Edge(const Edge&) = default;
	Edge(Edge&&) = default;
	Edge(const VertexType &v1, const VertexType &v2);

	Edge &operator=(const Edge&) = default;
	Edge &operator=(Edge&&) = default;
	bool operator ==(const Edge &e) const;

	template<typename U>
	friend std::ostream &operator <<(std::ostream &str, const Edge<U> &e);

	const VertexType *v;
	const VertexType *w;
	bool isBad = false;

	static_assert(std::is_floating_point_v<Edge<T>::Type>,
		"Type must be floating-point");
};

template<typename T>
bool
almost_equal(const Edge<T> &e1, const Edge<T> &e2)
{
	return	(almost_equal(*e1.v, *e2.v) && almost_equal(*e1.w, *e2.w)) ||
			(almost_equal(*e1.v, *e2.w) && almost_equal(*e1.w, *e2.v));
}

#endif

