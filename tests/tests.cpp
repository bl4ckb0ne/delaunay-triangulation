#define CATCH_CONFIG_MAIN
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

TEST_CASE("Delaunay triangulation should be able to handle 10000 points as float", "[DelaunayTest]") {
    std::vector<Vector2<float> > points(1e4);
    srand(666);
    for (size_t i=0; i < 1e4; ++i)
    {
        float x = (float)rand() / (float)RAND_MAX;
        float y = (double)rand() / (float)RAND_MAX;
        points.at(i) = Vector2<float>(x, y);
    }
    REQUIRE(10000 == points.size());
    Delaunay<float> triangulation;
    const std::vector<Triangle<float> > triangles = triangulation.triangulate(points);
}

TEST_CASE("Delaunay triangulation should be able to handle 10000 points as double", "[DelaunayTest]") {
    std::vector<Vector2<double> > points(1e4);
    srand(666);
    for (size_t i=0; i < 1e4; ++i)
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        points.at(i) = Vector2<double>(x, y);
    }
    REQUIRE(10000 == points.size());
    Delaunay<double> triangulation;
    const std::vector<Triangle<double> > triangles = triangulation.triangulate(points);
}
