#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "triangle.h"

#include <vector>

typedef Vector2<float> Vec2f;

class Delaunay
{
	public:
		static std::vector<Triangle> triangulate(std::vector<Vec2f> &vertices);
		static float quatCross(float a, float b, float c);
		static float crossProduct(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);
		static bool isFlatAngle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);   
 
};

#endif
