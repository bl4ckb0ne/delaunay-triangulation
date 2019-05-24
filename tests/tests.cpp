#define CATCH_CONFIG_MAIN
#include <random>
#include <catch2/catch.hpp>
#include "delaunay.h"

TEST_CASE("Delaunay triangulation should be able to triangulate 3 points as float", "[DelaunayTest]") {
    std::vector<Vector2<float> > points;
    points.push_back(Vector2<float>(0.0f, 0.0f));
    points.push_back(Vector2<float>(1.0f, 0.0f));
    points.push_back(Vector2<float>(0.0f, 1.0f));
    Delaunay<float> triangulation;
    const std::vector<Triangle<float> > triangles = triangulation.triangulate(points);
    REQUIRE(1 == triangles.size());
    // const std::vector<Edge<float> > edges = triangulation.getEdges();
}

TEST_CASE( "Delaunay triangulation should be able to triangulate 3 points as double", "[DelaunayTest]" ) {
    std::vector<Vector2<double> > points;
    points.push_back(Vector2<double>(0.0, 0.0));
    points.push_back(Vector2<double>(1.0, 0.0));
    points.push_back(Vector2<double>(0.0, 1.0));
    Delaunay<double> triangulation;
    const std::vector<Triangle<double> > triangles = triangulation.triangulate(points);
    REQUIRE(1 == triangles.size());
    // const std::vector<Edge<double> > edges = triangulation.getEdges();
}

TEST_CASE("Delaunay triangulation should be able to handle duplicated 3 points as double", "[DelaunayTest]") {
    std::vector<Vector2<double> > points;
    points.push_back(Vector2<double>(0.0, 0.0));
    points.push_back(Vector2<double>(0.0, 0.0));
    points.push_back(Vector2<double>(1.0, 0.0));
    points.push_back(Vector2<double>(0.0, 1.0));
    Delaunay<double> triangulation;
    const std::vector<Triangle<double> > triangles = triangulation.triangulate(points);
    REQUIRE(1 == triangles.size());
    // const std::vector<Edge<double> > edges = triangulation.getEdges();
}

std::default_random_engine eng(std::random_device{}());

TEST_CASE("Delaunay triangulation should be able to handle 10000 points as float", "[DelaunayTest]") {
	std::uniform_real_distribution<float> dist(0,
			std::numeric_limits<float>::max());
    std::vector<Vector2<float> > points(1e4);
    for (size_t i=0; i < 1e4; ++i)
    {
        const float x = dist(eng);
        const float y = dist(eng);
        points.at(i) = Vector2<float>(x, y);
    }
    REQUIRE(10000 == points.size());
    Delaunay<float> triangulation;
    const std::vector<Triangle<float> > triangles = triangulation.triangulate(points);
}

TEST_CASE("Delaunay triangulation should be able to handle 10000 points as double", "[DelaunayTest]") {
	std::uniform_real_distribution<double> dist(0,
			std::numeric_limits<double>::max());
    std::vector<Vector2<double> > points(1e4);
    for (size_t i=0; i < 1e4; ++i)
    {
        const double x = dist(eng);
        const double y = dist(eng);
        points.at(i) = Vector2<double>(x, y);
    }
    REQUIRE(10000 == points.size());
    Delaunay<double> triangulation;
    const std::vector<Triangle<double> > triangles = triangulation.triangulate(points);
}
