#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

struct Edge
{
	using VertexType = Vector2;

	Edge() = default;
	Edge(const Edge&) = default;
	Edge(Edge&&) = default;
	Edge(const VertexType &_p1, const VertexType &_p2);

	Edge &operator=(const Edge&) = default;
	Edge &operator=(Edge&&) = default;
	bool operator ==(const Edge &e);
	friend std::ostream &operator <<(std::ostream &str, const Edge &e);

	VertexType p1;
	VertexType p2;
	bool isBad = false;
};

bool almost_equal(const Edge &e1, const Edge &e2);

#endif

