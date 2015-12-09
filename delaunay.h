#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "triangle.h"

#include <vector>

typedef Vector2<float> Vec2f;

class Delaunay
{
	public:
		std::vector<Triangle> triangulate(std::vector<Vec2f> &vertices);
};

#endif
