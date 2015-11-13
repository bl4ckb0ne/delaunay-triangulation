#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

typedef Vector2<float> Vec2f;

class Edge
{
	public:
		Edge(const Vec2f &p1, const Vec2f &p2) : p1(p1), p2(p2) {};

		inline float length() { return p1.dist(p2); };
		Vec2f getMidPoint() {
			return Vec2f((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
		};

		Vec2f p1;
		Vec2f p2;
	
};

inline std::ostream &operator << (std::ostream &str, Edge const &e)
{
	return str << e.p1 << "," << e.p2;
}

inline bool operator == (const Edge & e1, const Edge & e2)
{
	return 	(e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
			(e1.p1 == e2.p2 && e1.p2 == e2.p1);
}

#endif 

