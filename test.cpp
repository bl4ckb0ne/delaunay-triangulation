#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <cmath>
#include "vector2.h"
#include "vector3.h"
#include "edge.h"
#include "triangle.h"
#include "delaunay.h"

typedef Vector2<float> Vec2f;

TEST_CASE("Vector2", "[vector2.h]")
{
	SECTION("Creating a vector2<float> with no parameters")
	{
		Vec2f p;
		REQUIRE(p.getX() == 0);
		REQUIRE(p.getY() == 0);
	}

	SECTION("Creating a vector2<float> with (0, 0)")
	{
		Vec2f p(0, 0);
		REQUIRE(p.getX() == 0);
		REQUIRE(p.getY() == 0);
	}

	SECTION("Creating a vector2<float> with (10, 10)")
	{
		Vec2f p(0, 0);
		REQUIRE(p.getX() == 0);
		REQUIRE(p.getY() == 0);	
	}	
	
	SECTION("Creating a vector2<float> by copy")
	{
		Vec2f p1(20, 50);
		Vec2f p2(p1);
		REQUIRE(p2.getX() == p1.getX());
		REQUIRE(p2.getY() == p1.getY());	
	}

	SECTION("Getters")	
	{
		Vec2f p(10, 10);
		REQUIRE(p.getX() == 10);
		REQUIRE(p.getY() == 10);
	}

	SECTION("Setters")
	{
		Vec2f p(0, 0);
		p.setX(30);
		p.setY(40);
		REQUIRE(p.getX() == 30);
		REQUIRE(p.getY() == 40);
	}

	SECTION("Dist")
	{
		Vec2f p(0, 0);
		Vec2f p1(2, 0);
		Vec2f p2(1, 1);
		REQUIRE(p.dist(p1) == 2.f);
		REQUIRE(p.dist(p2) == sqrtf(2));
	}

	SECTION("Dist2")
	{
		Vec2f p(0, 0);
		Vec2f p1(2, 0);
		Vec2f p2(1, 1);
		REQUIRE(p.dist2(p1) == 4.f);
		REQUIRE(p.dist2(p2) == 2.f);
	}

	SECTION("isInCircle")
	{
		Vec2f p(0, 0);
		REQUIRE(p.isInCircle(0, 0, 1));
		REQUIRE(p.isInCircle(1, 1, 2));
		REQUIRE(!(p.isInCircle(1, 1, 1)));
		REQUIRE(!(p.isInCircle(1, 1, 0.99)));
	}

	SECTION("==")
	{
		Vec2f p(0, 0);
		Vec2f p1(0, 0);
		Vec2f p2(10, 10);
		REQUIRE(p == p1);
		REQUIRE(!(p1 == p2));
	}
};

TEST_CASE("Edge", "[edge.h]")
{
	SECTION("Constructor via 2 points") 
	{
		Vec2f p(0, 0);
		Vec2f p1(1, 1);
		Edge e(p, p1);
		REQUIRE(e.getP1() == p);
		REQUIRE(e.getP2() == p1);
	}
	
	SECTION("Check if 2 edges are the same")
	{
		Vec2f p1(0, 0);
		Vec2f p2(1, 1);
		Vec2f p3(1, 2);
		Edge e1(p1, p2);
		Edge e2(p1, p2);
		Edge e3(p2, p1);
		Edge e4(p1, p3);
		REQUIRE(e1.same(e2));
		REQUIRE(e1.same(e3));
		REQUIRE(!(e1.same(e4)));	
	}

	SECTION("==")
	{
		Vec2f p1(0, 0);
		Vec2f p2(1, 1);
		Vec2f p3(1, 2);
		Edge e1(p1, p2);
		Edge e2(p1, p2);
		Edge e3(p2, p1);
		Edge e4(p1, p3);
		REQUIRE(e1 == e2);
		REQUIRE(!(e1 == e3));
		REQUIRE(!(e1 == e4));
	}
	
	SECTION("Middle")
	{
		Vec2f p(0, 0);
		Vec2f p1(2, 2);
		Edge e(p, p1);
		REQUIRE(e.getMidPoint().getX() == 1);
		REQUIRE(e.getMidPoint().getY() == 1);
	}
	
	SECTION("length")
	{
		Vec2f p(0, 0);
		Vec2f p1(1, 1);
		Edge e(p, p1);
		REQUIRE(e.length() == sqrtf(2));
	}
}

TEST_CASE("Triangle", "[triangle.h]")
{
	SECTION("Check points")
	{
		Vec2f p1(0, 0);
		Vec2f p2(2, 0);
		Vec2f p3(1, 1);
		Triangle t1(p1, p2, p3);
		REQUIRE(t1.getP1() == p1);
		REQUIRE(t1.getP2() == p2);
		REQUIRE(t1.getP3() == p3);
	}

	SECTION("Check edges")
	{
		Vec2f p1(0, 0);
		Vec2f p2(2, 0);
		Vec2f p3(1, 1);
		Triangle t1(p1, p2, p3);
		REQUIRE(t1.getE1() == Edge(p1, p2));
		REQUIRE(t1.getE2() == Edge(p2, p3));
		REQUIRE(t1.getE3() == Edge(p3, p1));
	}
		
	SECTION("A triangle cannot a flat angle")
	{
		Vec2f p1(-1, 0);
		Vec2f p2(0, 0);
		Vec2f p3(1, 0);
		REQUIRE(Delaunay::isFlatAngle(p1, p2, p3));
		Vec2f p4(0, 0);
		Vec2f p5(0, 1);
		Vec2f p6(1, 0);
		REQUIRE(!(Delaunay::isFlatAngle(p3, p4, p5)));
	}

	SECTION("Can evaluate the 3 sides length") 
	{
		Vec2f p1(0, 0);
		Vec2f p2(2, 0);
		Vec2f p3(1, 1);
    	Triangle t(p1, p2, p3);
    	Vector3<float>v(t.getSidesLength());
		REQUIRE(v.getX() == 2);
    	REQUIRE(v.getY() == sqrtf(2));
    	REQUIRE(v.getZ() == sqrtf(2));
	}

	SECTION("Can evaluate the coordinates of the triangle center")
	{
		Vec2f p1(-1, 0);
		Vec2f p2(1, 0);
		Vec2f p3(0, 1);
		Triangle t(p1, p2, p3);
		Vec2f v(t.getCenter());
		REQUIRE(v.getX() == 0);
		REQUIRE(v.getY() == (1.f / 3.f));
	}

	SECTION("Can evaluate the coordinates of the triangle circumcenter")
	{
		Vec2f p1(5, 5);
		Vec2f p2(10, 3);
		Vec2f p3(9, 15);
    	Triangle t(p1, p2, p3);
    	Vec2f v(t.getCircumCenter());
    	REQUIRE(v.getX() == 9.5);
    	REQUIRE(v.getY() == 9);
	}

	SECTION("Can evaluate the radius of the triangle circumcircle")
	{
		Vec2f p1(5, 5);
		Vec2f p2(10, 3);
		Vec2f p3(9, 15);
		Triangle t(p1, p2, p3);
		Vector3<float> v = t.getSidesLength();
		float circumRadius = ((v.getX() * v.getY() * v.getZ()) / Delaunay::quatCross(v.getX(), v.getY(), v.getZ()));
		REQUIRE(t.getCircumRadius() == circumRadius);	
	}
}
