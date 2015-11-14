#include "triangle.h"

#include <assert.h>
#include <math.h>

#include "delaunay.h"

Triangle::Triangle(const Vec2f &_p1, const Vec2f &_p2, const Vec2f &_p3)
	:	p1(_p1), p2(_p2), p3(_p3),
		e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1)
{
	//assert(!Delaunay::isFlatAngle(p1, p2, p3) && "angle(p1, p2, p3 is flat");
}

Triangle::Triangle(const Edge &_e1, const Edge &_e2, const Edge &_e3)
	:	p1(_e1.p1), p2(_e2.p1), p3(_e3.p1),
		e1(_e1), e2(_e2), e3(_e3)
{
	//assert(!Delaunay::isFlatAngle(p1, p2, p3) && "angle(p1, p2, p3 is flat");
}

Vec3f Triangle::getSidesLength()
{
	return Vec3f(e1.length(), e2.length(), e3.length());
}

bool Triangle::containsEdge(const Edge &e)
{
	return e1 == e || e2 == e || e3 == e;
}

bool Triangle::containsVertex(const Vec2f &v)
{
	return p1 == v || p2 == v || p3 == v; 
}

bool Triangle::circumCircleContains(const Vec2f &v)
{
	float ab = (p1.x * p1.x) + (p1.y * p1.y);
	float cd = (p2.x * p2.x) + (p2.y * p2.y);
	float ef = (p3.x * p3.x) + (p3.y * p3.y);

	float circum_x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) / (p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y)) / 2.f;
	float circum_y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) / (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x)) / 2.f;
	float circum_radius = sqrtf(((p1.x - circum_x) * (p1.x - circum_x)) + ((p1.y - circum_y) * (p1.y - circum_y)));

	float dist = sqrtf(((v.x - circum_x) * (v.x - circum_x)) + ((v.y - circum_y) * (v.y - circum_y)));
	return dist <= circum_radius;


}
