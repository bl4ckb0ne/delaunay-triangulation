#include "edge.h"

Edge::Edge(const Vec2f &p1, const Vec2f &p2)
	:	_p1(p1), _p2(p2)	
{}

bool Edge::same(const Edge &e) 
{
	return (((_p1 == e.getP1()) && (_p2 == e.getP2())) || 
			((_p1 == e.getP2()) && (_p2 == e.getP1())));
}

float Edge::length()
{
	return _p1.dist(_p2);
}

Vec2f Edge::getMidPoint()
{
	float x = _p1.getX() + (_p2.getX() - _p1.getX()) / 2; 
	float y = _p1.getY() + (_p2.getY() - _p1.getY()) / 2;    
	return Vec2f(x, y);
}
