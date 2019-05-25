#include "vector2.h"

Vector2::Vector2(const double vx, const double vy) :
	x(vx), y(vy)
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
	return hypot(x - v.x, y - v.y);
}

double
Vector2::norm2() const
{
	return x * x + y * y;
}

bool
Vector2::operator ==(const Vector2 &v)
{
	return (this->x == v.x) && (this->y == v.y);
}

std::ostream &
operator <<(std::ostream &str, const Vector2 &v)
{
	return str << "Point x: " << v.x << " y: " << v.y;
}

bool almost_equal(const Vector2 &v1, const Vector2 &v2, int ulp)
{
	return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}
