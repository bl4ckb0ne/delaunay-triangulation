#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "edge.h"
#include "triangle.h"

#include <vector>
#include <algorithm>

namespace dt {

template<typename T>
class Delaunay
{
	using Type = T;
	using VertexType = Vector2<Type>;
	using EdgeType = Edge<Type>;
	using TriangleType = Triangle<Type>;

	static_assert(std::is_floating_point<Delaunay<T>::Type>::value,
		"Type must be floating-point");

	std::vector<TriangleType> _triangles;
	std::vector<EdgeType> _edges;
	std::vector<VertexType> _vertices;

public:

	Delaunay() = default;
	Delaunay(const Delaunay&) = delete;
	Delaunay(Delaunay&&) = delete;

	const std::vector<TriangleType>& triangulate(std::vector<VertexType> &vertices);
	const std::vector<TriangleType>& getTriangles() const;
	const std::vector<EdgeType>& getEdges() const;
	const std::vector<VertexType>& getVertices() const;

	Delaunay& operator=(const Delaunay&) = delete;
	Delaunay& operator=(Delaunay&&) = delete;
};

} // namespace dt

#endif
