#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "triangle.h"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

typedef Vector2<float> Vec2f;

class Delaunay
{
	public:
		std::vector<Triangle> triangulate(std::vector<Vec2f> &vertices);
		std::vector<Triangle> getTriangles() { return _triangles; };
		std::vector<Edge> getEdges() { return _edges; };

	private:
		std::vector<Triangle> _triangles;
		std::vector<Edge> _edges;
};

#endif
