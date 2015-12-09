#include "delaunay.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <assert.h>

std::vector<Triangle*> Delaunay::triangulate(std::vector<Vec2f> &vertices)
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

	// Add the supertriangle to _triangles
	_triangles.push_back(new Triangle(p1, p2, p3));

	// For each Vec2f p in vertices do
	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::vector<Triangle*> badTriangles;
		std::vector<Edge*> polygon;

		// For each Triangle t in _triangles do
		for(auto t = begin(_triangles); t != end(_triangles); t++)
		{
			// If p is in the circum circle of t
			if((*t)->circumCircleContains(*p))
			{
				// Add t to badTriangles
				badTriangles.push_back(*t);
	
				// Add the edges of t to polygon
				polygon.push_back(&(*t)->e1);	
				polygon.push_back(&(*t)->e2);	
				polygon.push_back(&(*t)->e3);	
			}
		}

		// For each Triangle t in _triangles, if t is in badTriangles, delete t from _triangles
		_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [badTriangles](Triangle *t){
			for(auto bt = begin(badTriangles); bt != end(badTriangles); bt++)
			{	
				if((*bt) == t)
					return true;		
			}
			return false;
		}), end(_triangles));

		std::vector<Edge*> badEdges;
		
		// For each Edge e1 in polygon
		for(auto e1 = begin(polygon); e1 != end(polygon); e1++)
		{
			// For each edge e2 in polygon
			for(auto e2 = begin(polygon); e2 != end(polygon); e2++)
			{
				// If it's the same iterator, skip it
				if(e1 == e2)
					continue;
				
				// If polygon contains two equals Edge
				if(*e1 == *e2)
				{
					badEdges.push_back(*e1);	
					badEdges.push_back(*e2);	
				}
			}
		}

		// For each Edge e in polygon, if e is in badEdges, delete e from polygon
		polygon.erase(std::remove_if(begin(polygon), end(polygon), [badEdges](Edge *e){
			for(auto it = begin(badEdges); it != end(badEdges); it++)
			{
				if((*it) == e)
					return true;
			}
			return false;
		}), end(polygon));

		// For each Edge e in polygon, push a Triangle in _triangles formed by the two points of the edges and p
		for(auto e = begin(polygon); e != end(polygon); e++)
			_triangles.push_back(new Triangle((*(*e)).p1, (*(*e)).p2, *p));
	
	}

	// For each Triangle t in _triangles, delete t if in contains any points from the supertriangle
	_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](Triangle *t){
		return t->containsVertex(p1) || t->containsVertex(p2) || t->containsVertex(p3);
	}), end(_triangles));

	//
	for(auto t = begin(_triangles); t != end(_triangles); t++)
	{
		if(std::find(begin(_edges), end(_edges), &(*t)->e1) != end(_edges))
			_edges.push_back(&(*t)->e1);

		if(std::find(begin(_edges), end(_edges), &(*t)->e2) != end(_edges))
			_edges.push_back(&(*t)->e2);

		if(std::find(begin(_edges), end(_edges), &(*t)->e3) != end(_edges))
			_edges.push_back(&(*t)->e3);
	}

	return _triangles;
}
