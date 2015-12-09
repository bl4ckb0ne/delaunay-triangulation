#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

typedef Vector2<float> Vec2f;

class Edge
{
	public:
		Edge(const Vec2f &p1, const Vec2f &p2) : p1(p1), p2(p2) {};

		Vec2f p1;
		Vec2f p2;
};

inline std::ostream &operator << (std::ostream &str, Edge const &e)
{
	return str << "Edge " << e.p1 << ", " << e.p2;
}

inline bool operator == (const Edge & e1, const Edge & e2)
{
	return 	(e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
			(e1.p1 == e2.p2 && e1.p2 == e2.p1);
}

#endif 

