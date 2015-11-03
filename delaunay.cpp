#include "delaunay.h"

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
		for(auto i = edgesBuff.begin(); i != edgesBuff.end();)
		{
			bool deleted = false;
			for(auto j = edgesBuff.begin(); j != edgesBuff.end();)
			{
				if(i == j)
				{
					std::cout << "Same iterator lol! Passing" << std::endl;
					continue;
				}	
			
				if(i->same(*j))
				{
					std::cout << "Double! Process deleting" << std::endl;
					deleted = true;
					i = edgesBuff.erase(i);
					j = edgesBuff.erase(j);			
				}
				else
				{
					std::cout << "Nothing happend, incrementing j" << std::endl;
					j++;
				} 
			}
		
			if(!deleted)
			{
				std::cout << "Nothing happend, incrementing i" << std::endl;	
				i++;
			}
		}
		
		std::cout << "displaying edges" << std::endl;
		for(auto &e : edgesBuff)
			std::cout << e << std::endl;
	
    }


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
