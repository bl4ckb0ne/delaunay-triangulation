#include "delaunay.h"

const std::vector<Delaunay::TriangleType>&
Delaunay::triangulate(std::vector<VertexType> &vertices)
{
	// Store the vertices locally
	_vertices = vertices;

	// Determinate the super triangle
	double minX = vertices[0].x;
	double minY = vertices[0].y;
	double maxX = minX;
	double maxY = minY;

	for(std::size_t i = 0; i < vertices.size(); ++i)
	{
		if (vertices[i].x < minX) minX = vertices[i].x;
		if (vertices[i].y < minY) minY = vertices[i].y;
		if (vertices[i].x > maxX) maxX = vertices[i].x;
		if (vertices[i].y > maxY) maxY = vertices[i].y;
	}

	const double dx = maxX - minX;
	const double dy = maxY - minY;
	const double deltaMax = std::max(dx, dy);
	const double midx = half(minX + maxX);
	const double midy = half(minY + maxY);

	const VertexType p1(midx - 20 * deltaMax, midy - deltaMax);
	const VertexType p2(midx, midy + 20 * deltaMax);
	const VertexType p3(midx + 20 * deltaMax, midy - deltaMax);

	// Create a list of triangles, and add the supertriangle in it
	_triangles.push_back(TriangleType(p1, p2, p3));

	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::vector<EdgeType> polygon;

		for(auto & t : _triangles)
		{
			if(t.circumCircleContains(*p))
			{
				t.isBad = true;
				polygon.push_back(t.e1);
				polygon.push_back(t.e2);
				polygon.push_back(t.e3);
			}
		}

		_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [](TriangleType &t){
			return t.isBad;
		}), end(_triangles));

		for(auto e1 = begin(polygon); e1 != end(polygon); ++e1)
		{
			for(auto e2 = e1 + 1; e2 != end(polygon); ++e2)
			{
				if(almost_equal(*e1, *e2))
				{
					e1->isBad = true;
					e2->isBad = true;
				}
			}
		}

		polygon.erase(std::remove_if(begin(polygon), end(polygon), [](EdgeType &e){
			return e.isBad;
		}), end(polygon));

		for(const auto e : polygon)
			_triangles.push_back(TriangleType(e.p1, e.p2, *p));

	}

	_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](TriangleType &t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	}), end(_triangles));

	for(const auto t : _triangles)
	{
		_edges.push_back(t.e1);
		_edges.push_back(t.e2);
		_edges.push_back(t.e3);
	}

	return _triangles;
}

const std::vector<Delaunay::TriangleType>&
Delaunay::getTriangles() const
{
	return _triangles;
}

const std::vector<Delaunay::EdgeType>&
Delaunay::getEdges() const
{
	return _edges;
}

const std::vector<Delaunay::VertexType>&
Delaunay::getVertices() const
{
	return _vertices;
}
