#include "gtest/gtest.h"

#include "delaunay.h"

namespace {

// The fixture for testing class Foo.
class DelaunayTest : public ::testing::Test {
    protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    DelaunayTest() {
        // You can do set-up work for each test here.
    }
    virtual ~DelaunayTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
};


TEST_F(DelaunayTest, DelaunayFloat) {
    std::vector<Vector2<float> > points;
    points.push_back(Vector2<float>(0.0f, 0.0f));
    points.push_back(Vector2<float>(1.0f, 0.0f));
    points.push_back(Vector2<float>(0.0f, 1.0f));
    Delaunay<float> triangulation;
    const std::vector<Triangle<float> > triangles = triangulation.triangulate(points);
    EXPECT_EQ(1, triangles.size());
    // const std::vector<Edge<float> > edges = triangulation.getEdges();
}

TEST_F(DelaunayTest, DelaunayDouble) {
    std::vector<Vector2<double> > points;
    points.push_back(Vector2<double>(0.0, 0.0));
    points.push_back(Vector2<double>(1.0, 0.0));
    points.push_back(Vector2<double>(0.0, 1.0));
    Delaunay<double> triangulation;
    const std::vector<Triangle<double> > triangles = triangulation.triangulate(points);
    EXPECT_EQ(1, triangles.size());
    // const std::vector<Edge<float> > edges = triangulation.getEdges();
}

}   // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}