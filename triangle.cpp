#include "triangle.h"

#include <assert.h>

#include "delaunay.h"

Triangle::Triangle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
	:	_p1(p1), _p2(p2), _p3(p3),
		_e1(p1, p2), _e2(p2, p3), _e3(p3, p1)
{
	assert(!Delaunay::isFlatAngle(_p1, _p2, _p3) && "angle(p1, p2, p3 is flat");
}

Triangle::Triangle(const Edge &e1, const Edge &e2, const Edge &e3)
	:	_p1(e1.getP1()), _p2(e2.getP1()), _p3(e3.getP1()),
		_e1(e1), _e2(e2), _e3(e3)
{
	assert(!Delaunay::isFlatAngle(_p1, _p2, _p3) && "angle(p1, p2, p3 is flat");
}

bool Triangle::isCW()
{
	return(Delaunay::crossProduct(_p1, _p2, _p3) < 0);
}

bool Triangle::isCCW()
{
	return(Delaunay::crossProduct(_p1, _p2, _p3) > 0);
}

Vec3f Triangle::getSidesLength()
{
	return Vec3f(_e1.length(), _e2.length(), _e3.length());
}

Vec2f Triangle::getCenter()
{
	float x = (_p1.getX() + _p2.getX() + _p3.getX()) / 3;
	float y = (_p1.getY() + _p2.getY() + _p3.getY()) / 3;
	return Vec2f(x, y);
}

Vec3f Triangle::getCircumCircle()
{
	Vec2f v(getCircumCenter());
	return Vec3f(v.getX(), v.getY(), getCircumRadius());
}

Vec2f Triangle::getCircumCenter()
{
	float D = (	_p1.getX() * (_p2.getY() - _p3.getY()) +
				_p2.getX() * (_p3.getY() - _p1.getY()) + 
				_p3.getX() * (_p1.getY() - _p2.getY())) * 2;

	float x = ((_p1.getX() * _p1.getX() + _p1.getY() * _p1.getY()) * (_p2.getY() - _p3.getY()) +
			   (_p2.getX() * _p2.getX() + _p2.getY() * _p2.getY()) * (_p3.getY() - _p1.getY()) +
			   (_p3.getX() * _p3.getX() + _p3.getY() * _p3.getY()) * (_p1.getY() - _p2.getY()));


	float y = ((_p1.getX() * _p1.getX() + _p1.getY() * _p1.getY()) * (_p3.getX() - _p2.getX()) +
			   (_p2.getX() * _p2.getX() + _p2.getY() * _p2.getY()) * (_p1.getX() - _p3.getX()) +
			   (_p3.getX() * _p3.getX() + _p3.getY() * _p3.getY()) * (_p2.getX() - _p1.getX()));

	return Vec2f((x / D), (y / D));
}

float Triangle::getCircumRadius()
{
	Vec3f v(getSidesLength());
	return ((v.getX() * v.getY() * v.getZ()) / Delaunay::quatCross(v.getX(), v.getY(), v.getZ()));
}

float Triangle::getArea()
{
	Vec3f v(getSidesLength());
	return (Delaunay::quatCross(v.getX(), v.getY(), v.getZ()) / 4);	
}

bool Triangle::inCircumCircle(Vec2f &p)
{
	Vec3f v(getCircumCircle());
	return p.isInCircle(v.getX(), v.getY(), v.getZ());
}
