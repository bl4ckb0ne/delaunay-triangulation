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
		std::vector<std::shared_ptr<Triangle> > triangulate(std::vector<Vec2f> &vertices);
		std::vector<std::shared_ptr<Triangle> > getTriangles() { return _triangles; };
		std::vector<std::shared_ptr<Edge>> getEdges() { return _edges; };

	private:
		std::vector<std::shared_ptr<Triangle> > _triangles;
		std::vector<std::shared_ptr<Edge> > _edges;
};

#endif
