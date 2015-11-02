#include "delaunay.h"

#include <cmath>
#include <assert.h>

std::vector<Triangle> Delaunay::triangulate(std::vector<Vec2f> &vertices)
{
	const int nvertices = vertices.size();

	assert(nvertices > 2 && "Need more thant 3 vertices to triangulate");

	const int trmax = nvertices * 4; 	

	float minX = vertices[0].getX();
	float minY = vertices[0].getY();
	float maxX = minX;
	float maxY = minY;

	for(std::size_t i = 0; i < vertices.size(); ++i) {
		vertices[i].id = static_cast<int>(i);
		if (vertices[i].getX() < minX) 
			minX = vertices[i].getX();
    	if (vertices[i].getY() < minY)
			minY = vertices[i].getY();
    	if (vertices[i].getX() > maxX)
			maxX = vertices[i].getX();
    	if (vertices[i].getY() > maxY)
			maxY = vertices[i].getY();
	}
	
	float dx = maxX - minX;
	float dy = maxY - minY;
	float deltaMax = std::max(dx, dy);
	float midx = (minX + maxX) * 0.5;
	float midy = (minY + maxY) * 0.5;

	Vec2f p1(midx - 2 * deltaMax, midy - deltaMax);
	Vec2f p2(midx, midy + 2 * deltaMax);
	Vec2f p3(midx + 2 * deltaMax, midy - deltaMax);	
	p1.id = nvertices + 1;
	p2.id = nvertices + 2;
	p3.id = nvertices + 3;
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);


	std::vector<Triangle> triangles;
	triangles.push_back(Triangle(p1, p2, p3));

	for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
		std::vector<Edge> edges;

		for(int j = static_cast<int>(triangles.size()); j-- > 0; ) {
			Triangle curTriangle = triangles[j];

			if (curTriangle.inCircumCircle(vertices[i])) {
				edges.push_back(curTriangle.getE1());
				edges.push_back(curTriangle.getE2());
				edges.push_back(curTriangle.getE3());
				triangles.erase(triangles.begin() + j);
			}	
		}

		for(int j = static_cast<int>(edges.size()) - 1; --j > 0; ) {
			for(int k = edges.size(); --k > j + 1; ) {
				if(edges[j].same(edges[k])) {
					edges.erase(edges.begin() + j);	
					edges.erase(edges.begin() + k - 1);
					--k;
				}
			}
		}

		for(int j = 0; j < static_cast<int>(edges.size()); ++j) {
			int n = triangles.size();
			std::cout << n << " " << trmax << std::endl;
			assert(n <= trmax && "Generated more than needed triangles");	
			triangles.push_back(Triangle(edges[j].getP1(), edges[j].getP2(), vertices[i]));
		}
	}

	for(int i = static_cast<int>(triangles.size()); --i > 0; ) {
		Triangle triangle = triangles[i];
		if(triangle.getP1().id > static_cast<int>(nvertices) ||
			triangle.getP2().id > static_cast<int>(nvertices) ||
			triangle.getP3().id > static_cast<int>(nvertices)) {
			triangles.erase(triangles.begin() + i);
		}
	}

	return triangles;
}

/*	
 *	Triangle semi-perimeter by Heron's formula
 */	
float Delaunay::quatCross(float a, float b, float c)
{
	float p = (a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c);
	return sqrtf(p);
}

/*
 *	Cross product (p1-p2, p2-p3)
 */
float Delaunay::crossProduct(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
{
	float x1 = p2.getX() - p1.getX();
	float x2 = p3.getX() - p2.getX();
	float y1 = p2.getY() - p1.getY();
	float y2 = p3.getY() - p2.getY();
	return x1 * y2 - y1 * x2;
}

bool Delaunay::isFlatAngle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
{
	return(Delaunay::crossProduct(p1, p2, p3) == 0);	
}    
