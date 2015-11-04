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
//using Vec2f = Vector2<float>; 

TEST_CASE("Vector2", "[vector2.h]")
{
	SECTION("Creating a vector2<float> with no parameters")
	{
		Vec2f p;
		REQUIRE(p.getX() == 0.f);
		REQUIRE(p.getY() == 0.f);
	}

	SECTION("Creating a vector2<float> with (0, 0)")
	{
		Vec2f p(0.f, 0.f);
		REQUIRE(p.getX() == 0.f);
		REQUIRE(p.getY() == 0.f);
	}

	SECTION("Creating a vector2<float> with (10, 10)")
	{
		Vec2f p(10.f, 10.f);
		REQUIRE(p.getX() == 10.f);
		REQUIRE(p.getY() == 10.f);	
	}	
	
	SECTION("Creating a vector2<float> by copy")
	{
		Vec2f p1(20.f, 50.f);
		Vec2f p2(p1);
		REQUIRE(p2.getX() == p1.getX());
		REQUIRE(p2.getY() == p1.getY());	
	}

	SECTION("Getters")	
	{
		Vec2f p(10.f, 10.f);
		REQUIRE(p.getX() == 10.f);
		REQUIRE(p.getY() == 10.f);
	}

	SECTION("Setters")
	{
		Vec2f p(0.f, 0.);
		p.setX(30.f);
		p.setY(40.f);
		REQUIRE(p.getX() == 30.f);
		REQUIRE(p.getY() == 40.f);
	}

	SECTION("Dist")
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(2.f, 0.f);
		Vec2f p2(1.f, 1.f);
		REQUIRE(p.dist(p1) == 2.f);
		REQUIRE(p.dist(p2) == sqrtf(2));
	}

	SECTION("Dist2")
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(2.f, 0.f);
		Vec2f p2(1.f, 1.f);
		REQUIRE(p.dist2(p1) == 4.f);
		REQUIRE(p.dist2(p2) == 2.f);
	}

	SECTION("isInCircle")
	{
		Vec2f p(0.f, 0.f);
		REQUIRE(p.isInCircle(0, 0, 1.f));
		REQUIRE(p.isInCircle(1, 1, 2.f));
		REQUIRE_FALSE(p.isInCircle(1, 1, 1.f));
		REQUIRE_FALSE(p.isInCircle(1, 1, 0.99f));
	}

	SECTION("==")
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(0.f, 0.f);
		Vec2f p2(10.f, 10.f);
		REQUIRE(p == p1);
		REQUIRE_FALSE(p1 == p2);
	}
};

TEST_CASE("Edge", "[edge.h]")
{
	SECTION("Constructor via 2 points") 
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(1.f, 1.f);
		Edge e(p, p1);
		REQUIRE(e.getP1() == p);
		REQUIRE(e.getP2() == p1);
	}
	
	SECTION("Check if 2 edges are the same")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(1.f, 1.f);
		Vec2f p3(1.f, 2.f);
		Edge e1(p1, p2);
		Edge e2(p1, p2);
		Edge e3(p2, p1);
		Edge e4(p1, p3);
		REQUIRE(e1.same(e2));
		REQUIRE(e1.same(e3));
		REQUIRE_FALSE(e1.same(e4));	
	}

	SECTION("==")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(1.f, 1.f);
		Vec2f p3(1.f, 2.f);
		Edge e1(p1, p2);
		Edge e2(p1, p2);
		Edge e3(p2, p1);
		Edge e4(p1, p3);
		REQUIRE(e1 == e2);
		REQUIRE_FALSE(e1 == e3);
		REQUIRE_FALSE(e1 == e4);
	}
	
	SECTION("Middle")
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(2.f, 2.f);
		Edge e(p, p1);
		REQUIRE(e.getMidPoint().getX() == 1.f);
		REQUIRE(e.getMidPoint().getY() == 1.f);
	}
	
	SECTION("length")
	{
		Vec2f p(0.f, 0.f);
		Vec2f p1(1.f, 1.f);
		Edge e(p, p1);
		REQUIRE(e.length() == sqrtf(2));
	}
}

TEST_CASE("Triangle", "[triangle.h]")
{
	SECTION("Check points")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(2.f, 0.f);
		Vec2f p3(1.f, 1.f);
		Triangle t1(p1, p2, p3);
		REQUIRE(t1.getP1() == p1);
		REQUIRE(t1.getP2() == p2);
		REQUIRE(t1.getP3() == p3);
	}

	SECTION("Check edges")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(2.f, 0.f);
		Vec2f p3(1.f, 1.f);
		Triangle t1(p1, p2, p3);
		REQUIRE(t1.getE1() == Edge(p1, p2));
		REQUIRE(t1.getE2() == Edge(p2, p3));
		REQUIRE(t1.getE3() == Edge(p3, p1));
	}
		
	SECTION("A triangle cannot a flat angle")
	{
		Vec2f p1(-1.f, 0.f);
		Vec2f p2(0.f, 0.f);
		Vec2f p3(1.f, 0.f);
		REQUIRE(Delaunay::isFlatAngle(p1, p2, p3));
		Vec2f p4(0.f, 0.f);
		Vec2f p5(0.f, 1.f);
		Vec2f p6(1.f, 0.f);
		REQUIRE_FALSE(Delaunay::isFlatAngle(p3, p4, p5));
	}

	SECTION("Can evaluate the 3 sides length") 
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(2.f, 0.f);
		Vec2f p3(1.f, 1.f);
    	Triangle t(p1, p2, p3);
    	Vector3<float>v(t.getSidesLength());
		REQUIRE(v.getX() == 2.f);
    	REQUIRE(v.getY() == sqrtf(2));
    	REQUIRE(v.getZ() == sqrtf(2));
	}

	SECTION("Can evaluate the coordinates of the triangle center")
	{
		Vec2f p1(-1.f, 0.f);
		Vec2f p2(1.f, 0.f);
		Vec2f p3(0.f, 1.f);
		Triangle t(p1, p2, p3);
		Vec2f v(t.getCenter());
		REQUIRE(v.getX() == 0.f);
		REQUIRE(v.getY() == (1.f / 3.f));
	}

	SECTION("Can evaluate the coordinates of the triangle circumcenter")
	{
		Vec2f p1(5.f, 5.f);
		Vec2f p2(10.f, 3.f);
		Vec2f p3(9.f, 15.f);
    	Triangle t(p1, p2, p3);
    	Vec2f v(t.getCircumCenter());
    	REQUIRE(v.getX() == 9.5f);
    	REQUIRE(v.getY() == 9.f);
	}

	SECTION("Can evaluate the radius of the triangle circumcircle")
	{
		Vec2f p1(5.f, 5.f);
		Vec2f p2(10.f, 3.f);
		Vec2f p3(9.f, 15.f);
		Triangle t(p1, p2, p3);
		Vector3<float> v = t.getSidesLength();
		float circumRadius = ((v.getX() * v.getY() * v.getZ()) / Delaunay::quatCross(v.getX(), v.getY(), v.getZ()));
		REQUIRE(t.getCircumRadius() == circumRadius);	
	}

	SECTION("Can evaluate both circumcenter and circumradius")
	{
		Vec2f p1(5.f, 5.f);
		Vec2f p2(10.f, 3.f);
		Vec2f p3(9.f, 15.f);
		Triangle t(p1, p2, p3);
		Vector3<float> v = t.getCircumCircle();
		REQUIRE(v.getX() == 9.5f);
		REQUIRE(v.getY() == 9.f);
	}

	SECTION("Can test if a given point lies in a triangle's circumcircle")
	{
		Vec2f p1(0.f, 0.5f);
		Vec2f p2(1.f, 1.f);
		Vec2f p3(1.01f, 1.01f);
		Triangle t(Vec2f(-1.f, 0.f), Vec2f(1.f, 0.f), Vec2f(1.f, 1.f));
		REQUIRE(t.inCircumCircle(p1));
		REQUIRE(t.inCircumCircle(p2));
		REQUIRE_FALSE(t.inCircumCircle(p3));
	}

	SECTION("Can evaluate the area of a triangle")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(1.f, 0.f);
		Vec2f p3(1.f, 1.f);
		Triangle t(p1, p2, p3);
		Vector3<float> v = t.getCircumCircle();
		REQUIRE(t.getArea() == 0.5f);	
	}

	SECTION("Can evaluate if triangle is defined clockwise")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(-1.f, 0.f);
		Vec2f p3(1.f, 1.f);
		REQUIRE(Triangle(p1, p2, p3).isCW());
		REQUIRE_FALSE(Triangle(p1, p3, p2).isCW());
	}

	SECTION("Can also evaluate if triangle is defined counter-clockwise")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(1.f, 0.f);
		Vec2f p3(1.f, 1.f);
		REQUIRE(Triangle(p1, p2, p3).isCCW());
		REQUIRE_FALSE(Triangle(p1, p3, p2).isCCW());
	}

	SECTION("Check if the triangle contains an edge")
	{
		Vec2f p1(0.f, 0.f);
		Vec2f p2(1.f, 0.f);
		Vec2f p3(1.f, 1.f);
		Vec2f p4(2.f, 1.f);
		Triangle t(p1, p2, p3);	
		REQUIRE(t.containsEdge(Edge(p1, p2)));
		REQUIRE(t.containsEdge(Edge(p1, p3)));
		REQUIRE(t.containsEdge(Edge(p2, p1)));
		REQUIRE(t.containsEdge(Edge(p2, p3)));
		REQUIRE(t.containsEdge(Edge(p3, p1)));
		REQUIRE(t.containsEdge(Edge(p3, p2)));
		REQUIRE_FALSE(t.containsEdge(Edge(p1, p4)));
	}
}

TEST_CASE("Delaunay", "[delaunay.h]")
{
	/*
	SECTION("Throws an assert for 1 vertice")
	{
		std::vector<Vec2f> v;
		v.push_back(Vec2f(0, 0));
		CHECK_THROWS(Delaunay::triangulate(v));
	}
	*/

	SECTION("Return a unique triangle made when receiving 3 vertices")
	{
		std::vector<Vec2f> v = {Vec2f(0.f, 0.f), Vec2f(2.f, 0.f), Vec2f(1.f, 1.f)};
		std::vector<Triangle> t = Delaunay::triangulate(v);
		for(auto &i : t) 
			std::cout << i << std::endl;

		std::cout << "Those are the triangles" << std::endl;
	}
}
