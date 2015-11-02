#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

typedef Vector2<float> Vec2f;

class Edge
{
	public:
		Edge(const Vec2f &p1, const Vec2f &p2);

		Vec2f const & getP1() const { return _p1; }
		Vec2f const & getP2() const { return _p2; }

		bool same(const Edge &e);
		float length();
		Vec2f getMidPoint();

	private:
		Vec2f _p1;
		Vec2f _p2;
	
};

inline std::ostream &operator << (std::ostream &str, Edge const &e)
{
	return str << e.getP1() << "," << e.getP2();
}

inline bool operator == (const Edge & e1, const Edge & e2)
{
	return 	e1.getP1() == e2.getP1() && e1.getP2() == e2.getP2();
}


#endif 

