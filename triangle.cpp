#include "triangle.h"

#include <assert.h>
#include <math.h>

#include "delaunay.h"

Triangle::Triangle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
	:	_p1(p1), _p2(p2), _p3(p3),
		_e1(p1, p2), _e2(p2, p3), _e3(p3, p1)
{
	//assert(!Delaunay::isFlatAngle(_p1, _p2, _p3) && "angle(p1, p2, p3 is flat");
}

Triangle::Triangle(const Edge &e1, const Edge &e2, const Edge &e3)
	:	_p1(e1.getP1()), _p2(e2.getP1()), _p3(e3.getP1()),
		_e1(e1), _e2(e2), _e3(e3)
{
	//assert(!Delaunay::isFlatAngle(_p1, _p2, _p3) && "angle(p1, p2, p3 is flat");
}

Vec3f Triangle::getSidesLength()
{
	return Vec3f(_e1.length(), _e2.length(), _e3.length());
}

bool Triangle::inCircumCircle(Vec2f &p)
{
	Vec3f v(getCircumCircle());
	return p.isInCircle(v.getX(), v.getY(), v.getZ());
	/*
	float EPSILON = 0.000001f;
	float xc, yc;
	float y1y2 = fabs(_p1.getY() - _p2.getY());
	float y2y3 = fabs(_p2.getY() - _p3.getY());

	if(y1y2 < EPSILON && y2y3 < EPSILON)
		return false;

	if(y1y2 < EPSILON) 
	{
		float m2 = -(_p3.getX() - _p2.getX()) / (_p3.getY() - _p2.getY());
		float mx2 = (_p2.getX() + _p3.getX()) / 2.f;
		float my2 = (_p2.getY() + _p3.getY()) / 2.f;
		xc = (_p2.getX() + _p1.getX()) / 2.f;
		yc = m2 * (xc - mx2) + my2;
	}
	else if(fabs(_p3.getY() - _p2.getY()) < EPSILON)
	{
		float m1 = -(_p2.getX() - _p1.getX()) / (_p2.getY() - _p1.getY());
		float mx1 = (_p1.getX() + _p2.getX()) / 2.f;
		float my1 = (_p1.getY() + _p2.getY()) / 2.f;
		xc = (_p3.getX() + _p2.getX() / 2.f);
		yc = m1 * (xc - mx1) + my1;
	}
	else
	{
		float m1 = -(_p2.getX() - _p1.getX()) / (_p2.getY() - _p1.getY());
		float m2 = -(_p3.getX() - _p2.getX()) / (_p3.getY() - _p2.getY());
		float mx1 = (_p1.getX() + _p2.getX()) / 2.f;
		float mx2 = (_p2.getX() + _p3.getX()) / 2.f;
		float my1 = (_p1.getY() + _p2.getY()) / 2.f;
		float my2 = (_p2.getY() + _p3.getY()) / 2.f;
		xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2); 
		yc = m1 * (xc - mx1) + my1;
	}
	

	float dx = _p2.getX() - xc;
	float dy = _p2.getY() - yc;
	float rsqr = dx * dx + dy * dy;
	dx = p.getX() - xc;
	dy = p.getY() - yc;
	float drsqr = dx * dx + dy + dy;
	return ((drsqr <= rsqr) ? true : false);
	*/
}

Vec3f Triangle::getCircumCircle()
{
	Vec2f v(getCircumCenter());
	float r = getCircumRadius();
	return Vec3f(v.getX(), v.getY(), r);
}

Vec2f Triangle::getCircumCenter()
{
	float d = 	(_p1.getX() * (_p2.getY() - _p3.getY()) +
				 _p2.getX() * (_p3.getY() - _p1.getY()) +
				 _p3.getX() * (_p1.getY() - _p2.getY())) * 2;
	
	float x = (( _p1.getX() * _p1.getX() + _p1.getY() * _p1.getY()) * (_p2.getY() - _p3.getY()) +
             ( _p2.getX() * _p2.getX() + _p2.getY() * _p2.getY()) * (_p3.getY() - _p1.getY()) +
             ( _p3.getX() * _p3.getX() + _p3.getY() * _p3.getY()) * (_p1.getY() - _p2.getY()));

	float y = (( _p1.getX() * _p1.getX() + _p1.getY() * _p1.getY()) * (_p3.getX() - _p2.getX()) +
             ( _p2.getX() * _p2.getX() + _p2.getY() * _p2.getY()) * (_p1.getX() - _p3.getX()) +
             ( _p3.getX() * _p3.getX() + _p3.getY() * _p3.getY()) * (_p2.getX() - _p1.getX()));

	return Vec2f(x / d, y / d);
 
}

float Triangle::getCircumRadius()
{
	Vec3f v(getSidesLength());
	float a = v.getX();
	float b = v.getY();
	float c = v.getZ();
	float p = (a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c);
	
	return (a * b * c / sqrtf(p));
}

bool Triangle::containsEdge(const Edge &e)
{
	return _e1 == e || _e2 == e || _e3 == e;
}

bool Triangle::containsVertex(const Vec2f &v)
{
	return _p1 == v || _p2 == v || _p3 == v; 
}

bool Triangle::same(const Triangle &t)
{
	return	(_p1 == t.getP1() || _p1 == t.getP2() || _p1 == t.getP3()) &&
			(_p2 == t.getP1() || _p2 == t.getP2() || _p2 == t.getP3()) && 
			(_p3 == t.getP1() || _p3 == t.getP2() || _p3 == t.getP3());	
}
