#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "triangle.h"

#include <vector>

typedef Vector2<float> Vec2f;

class Delaunay
{
	public:
		static std::vector<Triangle> delaunay(std::vector<Vec2f> &vertices);
		static std::vector<Triangle> bowyerWatson(std::vector<Vec2f> &vertices);
		static float crossProduct(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);
		static bool isFlatAngle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);   
 
};

#endif
