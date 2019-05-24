#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "edge.h"
#include "triangle.h"

#include <vector>
#include <algorithm>

class Delaunay
{
public:
	using TriangleType = Triangle;
	using EdgeType = Edge;
	using VertexType = Vector2;

	Delaunay() = default;
	Delaunay(const Delaunay&) = delete;
	Delaunay(Delaunay&&) = delete;

	const std::vector<TriangleType>& triangulate(std::vector<VertexType> &vertices);
	const std::vector<TriangleType>& getTriangles() const;
	const std::vector<EdgeType>& getEdges() const;
	const std::vector<VertexType>& getVertices() const;

	Delaunay& operator=(const Delaunay&) = delete;
	Delaunay& operator=(Delaunay&&) = delete;

private:
	std::vector<TriangleType> _triangles;
	std::vector<EdgeType> _edges;
	std::vector<VertexType> _vertices;
};

#endif
