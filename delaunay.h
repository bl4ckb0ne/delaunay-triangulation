#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "triangle.h"

#include <vector>

typedef Vector2<float> Vec2f;

class Delaunay
{
	public:
		const std::vector<Triangle>& triangulate(std::vector<Vec2f> &vertices);
		const std::vector<Triangle>& getTriangles() const { return _triangles; };
		const std::vector<Edge>& getEdges() const { return _edges; };

	private:
		std::vector<Triangle> _triangles;
		std::vector<Edge> _edges;
};

#endif
