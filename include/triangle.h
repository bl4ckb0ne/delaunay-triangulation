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
	Triangle(const VertexType &_p1, const VertexType &_p2, const VertexType &_p3);

	bool containsVertex(const VertexType &v) const;
	bool circumCircleContains(const VertexType &v) const;

	Triangle &operator=(const Triangle&) = default;
	Triangle &operator=(Triangle&&) = default;
	bool operator ==(const Triangle &t);
	friend std::ostream &operator <<(std::ostream &str, const Triangle &t);

	VertexType p1;
	VertexType p2;
	VertexType p3;
	EdgeType e1;
	EdgeType e2;
	EdgeType e3;
	bool isBad = false;
};

bool almost_equal(const Triangle &t1, const Triangle &t2);

#endif
