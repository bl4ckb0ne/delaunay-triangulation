#include "delaunay.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <assert.h>

std::vector<Triangle> Delaunay::delaunay(std::vector<Vec2f> &vertices)
{
	// Init stuff
	assert(vertices.size() > 2 && "Need more thant 3 vertices to triangulate");
	
	int trmax = vertices.size() * 4;

	// Determinate the super triangle
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float maxX = minX;
	float maxY = minY;

	for(std::size_t i = 0; i < vertices.size(); ++i) {
		if (vertices[i].x < minX) minX = vertices[i].x;
    	if (vertices[i].y < minY) minY = vertices[i].y;
    	if (vertices[i].x > maxX) maxX = vertices[i].x;
    	if (vertices[i].y > maxY) maxY = vertices[i].y;
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
	for(auto point = begin(vertices); point != end(vertices); point++) 
	{
		// Initialize the edges buffer
		std::vector<Edge> edgesBuff;
		
		// For each triangles currently in the triangle list	
		for(auto triangle = begin(triangleList); triangle != end(triangleList);) 
		{
			if(triangle->circumCircleContains(*point))
			{
				Edge tmp[3] = {triangle->e1, triangle->e2, triangle->e3};
				edgesBuff.push_back(triangle->e1);
				edgesBuff.push_back(triangle->e2);
				edgesBuff.push_back(triangle->e3);
				//edgesBuff.insert(end(edgesBuff), tmp, tmp + 3);	
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
				last = std::partition(ite, last, [&ite](Edge const &o){ return !(o == *ite); });
			else
				++ite;
		}
		
		// Remove all the duplicates, which have been shoved past "last".
		edgesBuff.erase(last, end(edgesBuff));

		// Add the triangle to the list
		for(auto edge = begin(edgesBuff); edge != end(edgesBuff); edge++)
			triangleList.push_back(Triangle(edge->p1, edge->p2, *point));	
	
    }

	// Remove any triangles from the triangle list that use the supertriangle vertices
	triangleList.erase(std::remove_if(begin(triangleList), end(triangleList), [p1, p2, p3](Triangle &t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	}), end(triangleList));

	// Remove the supertriangle vertices from the vertex list
	vertices.erase(std::remove_if(begin(vertices), end(vertices), [p1, p2, p3](Vec2f &v){
		return v == p1 || v == p2 || v == p3;
	}), end(vertices));

	std::cout << "For " << vertices.size() << " points" << std::endl;
	std::cout << "There is " << triangleList.size() << " triangles" << std::endl;

	return triangleList;
}

std::vector<Triangle> Delaunay::bowyerWatson(std::vector<Vec2f> &vertices)
{
	// Determinate the super triangle
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float maxX = minX;
	float maxY = minY;

	for(std::size_t i = 0; i < vertices.size(); ++i) 
	{
		if (vertices[i].x < minX) minX = vertices[i].x;
    	if (vertices[i].y < minY) minY = vertices[i].y;
    	if (vertices[i].x > maxX) maxX = vertices[i].x;
    	if (vertices[i].y > maxY) maxY = vertices[i].y;
	}
	
	float dx = maxX - minX;
	float dy = maxY - minY;
	float deltaMax = std::max(dx, dy);
	float midx = (minX + maxX) / 2.f;
	float midy = (minY + maxY) / 2.f;

	Vec2f p1(midx - 20 * deltaMax, midy - deltaMax);
	Vec2f p2(midx, midy + 20 * deltaMax);
	Vec2f p3(midx + 20 * deltaMax, midy - deltaMax);	
	
	// Create a list of triangles, and add the supertriangle in it
	std::vector<Triangle> triangleList = {Triangle(p1, p2, p3)};

	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::vector<Triangle> badTriangle;
	
		for(auto t = begin(triangleList); t != end(triangleList); t++)
		{
			if(t->circumCircleContains(*p))
				badTriangle.push_back(*t);
		}

		std::vector<Edge> polygon;
		
		for(auto t = begin(badTriangle); t != end(badTriangle); t++)
		{
			for(auto bt = begin(badTriangle); bt != end(badTriangle); bt++)
			{
				if(t == bt)
					continue;

				if(t->containsEdge(bt->e1)) 
					polygon.push_back(bt->e1);	
				else if(t->containsEdge(bt->e2))
					polygon.push_back(bt->e2);
				else if(t->containsEdge(bt->e3))				
					polygon.push_back(bt->e3);
			}
		}

		for(auto bt = begin(badTriangle); bt != end(badTriangle); bt++)
		{
			triangleList.erase(std::remove_if(begin(triangleList), end(triangleList), [bt](Triangle t) {
				return t == (*bt);
			}), end(triangleList));
		}

		for(auto e = begin(polygon); e != end(polygon); e++)
		{
			triangleList.push_back(Triangle(*e, Edge(e->p1, *p), Edge(e->p2, *p)));
		}
	}
	
	// Remove any triangles from the triangle list that use the supertriangle vertices
	triangleList.erase(std::remove_if(begin(triangleList), end(triangleList), [p1, p2, p3](Triangle &t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	}), end(triangleList));

	std::cout << "For " << vertices.size() << " points" << std::endl;
	std::cout << "There is " << triangleList.size() << " triangles" << std::endl;

	return triangleList;
}

/*
 *	Cross product (p1-p2, p2-p3)
 */
float Delaunay::crossProduct(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
{
	float x1 = p2.x - p1.x;
	float x2 = p3.x - p2.x;
	float y1 = p2.y - p1.y;
	float y2 = p3.y - p2.y;
	return x1 * y2 - y1 * x2;
}

bool Delaunay::isFlatAngle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
{
	return(Delaunay::crossProduct(p1, p2, p3) == 0);	
}    
