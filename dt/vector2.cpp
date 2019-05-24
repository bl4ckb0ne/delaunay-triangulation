#include "vector2.h"

Vector2::Vector2(double _x, double _y) :
	x(_x), y(_y)
{}

double
Vector2::dist2(const Vector2 &v) const
{
	const double dx = x - v.x;
	const double dy = y - v.y;
	return dx * dx + dy * dy;
}

double
Vector2::dist(const Vector2 &v) const
{
	return hypot(x - v.x, y - v.y);}
}

double
Vector2::norm2() const
{
	return x * x + y * y;
}
