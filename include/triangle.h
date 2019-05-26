#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "vector2.h"
#include "edge.h"
#include "numeric.h"

struct Triangle
{
	using EdgeType = Edge;
	using VertexType = Vector2;

	Triangle() = default;
	Triangle(const Triangle&) = default;
	Triangle(Triangle&&) = default;
	Triangle(const VertexType &v1, const VertexType &v2, const VertexType &v3);

	bool containsVertex(const VertexType &v) const;
	bool circumCircleContains(const VertexType &v) const;

	Triangle &operator=(const Triangle&) = default;
	Triangle &operator=(Triangle&&) = default;
	bool operator ==(const Triangle &t) const;
	friend std::ostream &operator <<(std::ostream &str, const Triangle &t);

	const VertexType *a;
	const VertexType *b;
	const VertexType *c;
	bool isBad = false;
};

bool almost_equal(const Triangle &t1, const Triangle &t2);

#endif
