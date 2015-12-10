#include "delaunay.h"

std::vector<std::shared_ptr<Triangle> > Delaunay::triangulate(std::vector<Vec2f> &vertices)
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
	_triangles.push_back(std::shared_ptr<Triangle>(new Triangle(p1, p2, p3)));

	// For each Vec2f p in vertices do
	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::cout << "Traitement du point " << *p << std::endl;
		std::cout << "Triangulation contains " << _triangles.size() << " elements" << std::endl;	

		std::vector<std::shared_ptr<Triangle> > badTriangles;
		std::vector<std::shared_ptr<Edge> > polygon;

		// For each Triangle t in _triangles do
		for(auto t = begin(_triangles); t != end(_triangles); t++)
		{
			std::cout << "Processing " << std::endl << **t << std::endl;

			// If p is in the circum circle of t
			if((*t)->circumCircleContains(*p))
			{
				std::cout << "Pushing bad triangle " << **t << std::endl;		

				// Add t to badTriangles
				badTriangles.push_back(*t);
	
				// Add the edges of t to polygon
				polygon.push_back(std::shared_ptr<Edge>(new Edge((*t)->e1)));	
				polygon.push_back(std::shared_ptr<Edge>(new Edge((*t)->e2)));	
				polygon.push_back(std::shared_ptr<Edge>(new Edge((*t)->e3)));	
			}
			else
			{
				std::cout << " does not contains " << *p << " in his circum center" << std::endl;
			}
		}

		// For each Triangle t in _triangles, if t is in badTriangles, delete t from _triangles
		_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [badTriangles](std::shared_ptr<Triangle> t){
			for(auto bt = begin(badTriangles); bt != end(badTriangles); bt++)
			{	
				if(*(*bt).get() == *t.get())
				{
					std::cout << "Removing bad triangle " << std::endl << **bt << " from triangulation" << std::endl;
					return true;
				}		
			}
			return false;
		}), end(_triangles));

		std::vector<std::shared_ptr<Edge> > badEdges;
		
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
					std::cout << "Pushing " << **e1 << " to badEdges" << std::endl;
					std::cout << "Pushing " << **e2 << " to badEdges" << std::endl;
					badEdges.push_back(*e1);	
					badEdges.push_back(*e2);	
				}
			}
		}

		// For each Edge e in polygon, if e is in badEdges, delete e from polygon
		polygon.erase(std::remove_if(begin(polygon), end(polygon), [badEdges](std::shared_ptr<Edge> e){
			for(auto it = begin(badEdges); it != end(badEdges); it++)
			{
				if(*(*it).get() == *e.get())
				{
					std::cout << "Removing " << *e << " from polygon" << std::endl;
					return true;
				}
			}
			return false;
		}), end(polygon));

		// For each Edge e in polygon, push a Triangle in _triangles formed by the two points of the edges and p
		for(auto e = begin(polygon); e != end(polygon); e++)
			_triangles.push_back(std::shared_ptr<Triangle>(new Triangle((*(*e)).p1, (*(*e)).p2, *p)));
	
	}

	// For each Triangle t in _triangles, delete t if in contains any points from the supertriangle
	_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](std::shared_ptr<Triangle> t){
		if(t->containsVertex(p1) || t->containsVertex(p2) || t->containsVertex(p3))
		{
			std::cout << "Removing " << *t << " from _triangles" << std::endl;
			return true;
		}
		return false;
	}), end(_triangles));

	// Copy the edges of Triangle t in _edges
	for(auto t = begin(_triangles); t != end(_triangles); t++)
	{
		_edges.push_back(std::shared_ptr<Edge>(new Edge((*t)->e1)));
		_edges.push_back(std::shared_ptr<Edge>(new Edge((*t)->e2)));
		_edges.push_back(std::shared_ptr<Edge>(new Edge((*t)->e3)));
	}
	
	return _triangles;
}
