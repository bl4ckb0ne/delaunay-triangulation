#include "delaunay.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <assert.h>

std::vector<Triangle> Delaunay::triangulate(std::vector<Vec2f> &vertices)
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

	std::cout << "Super triangle " << std::endl << Triangle(p1, p2, p3) << std::endl;
	
	// Create a list of triangles, and add the supertriangle in it
	std::vector<Triangle> triangulation = {Triangle(p1, p2, p3)};

	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::cout << "Traitement du point " << *p << std::endl;
		std::cout << "Triangulation contains " << triangulation.size() << " elements" << std::endl;	

		std::vector<Triangle> badTriangles;
		std::vector<Edge> polygon;

		for(auto t = begin(triangulation); t != end(triangulation); t++)
		{
			std::cout << "Processing " << std::endl << *t << std::endl;

			if(t->circumCircleContains(*p))
			{
				std::cout << "Pushing bad triangle " << *t << std::endl;
				badTriangles.push_back(*t);
				polygon.push_back(t->e1);	
				polygon.push_back(t->e2);	
				polygon.push_back(t->e3);	
			}
			else
			{
				std::cout << " does not contains " << *p << " in his circum center" << std::endl;
			}
		}

		triangulation.erase(std::remove_if(begin(triangulation), end(triangulation), [badTriangles](Triangle &t){
			for(auto bt = begin(badTriangles); bt != end(badTriangles); bt++)
			{	
				if(*bt == t)
				{
					std::cout << "Removing bad triangle " << std::endl << *bt << " from triangulation" << std::endl;
					return true;		
				}
			}
			return false;
		}), end(triangulation));

		std::vector<Edge> badEdges;
		for(auto e1 = begin(polygon); e1 != end(polygon); e1++)
		{
			for(auto e2 = begin(polygon); e2 != end(polygon); e2++)
			{
				if(e1 == e2)
					continue;
				
				if(*e1 == *e2)
				{
					badEdges.push_back(*e1);	
					badEdges.push_back(*e2);	
				}
			}
		}

		polygon.erase(std::remove_if(begin(polygon), end(polygon), [badEdges](Edge &e){
			for(auto it = begin(badEdges); it != end(badEdges); it++)
			{
				if(*it == e)
					return true;
			}
			return false;
		}), end(polygon));

		for(auto e = begin(polygon); e != end(polygon); e++)
			triangulation.push_back(Triangle(e->p1, e->p2, *p));
	
	
	}

	triangulation.erase(std::remove_if(begin(triangulation), end(triangulation), [p1, p2, p3](Triangle &t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	}), end(triangulation));

	return triangulation;
}
