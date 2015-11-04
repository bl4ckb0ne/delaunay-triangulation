#include "delaunay.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <assert.h>

std::vector<Triangle> Delaunay::triangulate(std::vector<Vec2f> &vertices)
{
	// Init stuff
	const int nvertices = vertices.size();
	assert(nvertices > 2 && "Need more thant 3 vertices to triangulate");
	const int trmax = nvertices * 4; 	

	// Determinate the super triangle
	float minX = vertices[0].getX();
	float minY = vertices[0].getY();
	float maxX = minX;
	float maxY = minY;

	for(std::size_t i = 0; i < vertices.size(); ++i) {
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
	float midx = (minX + maxX) / 2.f;
	float midy = (minY + maxY) / 2.f;

	Vec2f p1(midx - 20 * deltaMax, midy - deltaMax);
	Vec2f p2(midx, midy + 20 * deltaMax);
	Vec2f p3(midx + 20 * deltaMax, midy - deltaMax);	
	
	// Add the super triangle vertices to the end of the vertex list
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);

	// Add the super triangle to the triangle list
	std::vector<Triangle> triangleList = {Triangle(p1, p2, p3)};

	// For each point in the vertex list
	for(auto point = vertices.begin(); point != vertices.end(); point++) 
	{
		// Initialize the edges buffer
		std::vector<Edge> edgesBuff;
		
		// For each triangles currently in the triangle list	
		for(auto triangle = triangleList.begin(); triangle != triangleList.end();) 
		{
			if(triangle->inCircumCircle(*point))
			{
				Edge tmp[3] = {triangle->getE1(), triangle->getE2(), triangle->getE3()};
				edgesBuff.insert(edgesBuff.end(), tmp, tmp + 3);
				triangle = triangleList.erase(triangle);
			}
			else
			{
				triangle++;
			}
		}

		// Delete all doubly specified edges from the edge buffer
		// Black magic by https://github.com/MechaRage 

		auto ite = begin(edgesBuff), last = end(edgesBuff);
    
		while(ite != last) {
			// Search for at least one duplicate of the current element
			auto twin = std::find(ite + 1, last, *ite);
			if(twin != last)
				// If one is found, push them all to the end.
				last = std::partition(ite, last, [&ite](auto const &o){ return !(o == *ite); });
			else
				++ite;
		}
		
		// Remove all the duplicates, which have been shoved past "last".
		edgesBuff.erase(last, end(edgesBuff));


		//std::cout << "ITER" << std::endl;	
		//for(auto &e :edgesBuff)
		//	std::cout << e << std::endl;
	
		// Add the triangle to the list
		for(auto edge = begin(edgesBuff); edge != end(edgesBuff); edge++)
		{
			triangleList.push_back(Triangle(edge->getP1(), edge->getP2(), *point));
		}
		
	
    }

	// Remove any triangles from the triangle list that use the supertriangle vertices
	std::remove_if(begin(triangleList), end(triangleList), [p1, p2, p3](auto t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	});
	
	vertices.pop_back();
	vertices.pop_back();
	vertices.pop_back();

	return triangleList;
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
