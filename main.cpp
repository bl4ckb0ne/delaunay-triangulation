#include <iostream>
#include <vector>

#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

int main()
{
	std::vector<Vector2<float>> points;
	
	points.push_back(Vector2<float>(0, 0));	
	points.push_back(Vector2<float>(1, 3));	
	points.push_back(Vector2<float>(2, 5));	
	points.push_back(Vector2<float>(3, 4));	
	points.push_back(Vector2<float>(9, 5));	
	points.push_back(Vector2<float>(0, 2));	
	points.push_back(Vector2<float>(1, 0));	
	points.push_back(Vector2<float>(5, 3));	
	points.push_back(Vector2<float>(1, 9));	
	points.push_back(Vector2<float>(7, 3));	

	std::vector<Triangle> tr = Delaunay::triangulate(points);

	std::cout << tr.size() << " triangles" << std::endl;
	for(auto i = tr.begin(); i != tr.end(); i++) {
		std::cout << *i << std::endl;
	}
	
	return 0;
}
