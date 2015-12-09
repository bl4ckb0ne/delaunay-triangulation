#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "vector2.h"
#include "vector3.h"
#include "edge.h"

typedef Vector2<float> Vec2f;
typedef Vector3<float> Vec3f;

class Triangle
{
	public:
		Triangle(const Vec2f &_p1, const Vec2f &_p2, const Vec2f &_p3);
	
		bool containsVertex(const Vec2f &v);
		bool circumCircleContains(const Vec2f &v);
	
		Vec2f p1;
		Vec2f p2;
		Vec2f p3;
		Edge e1;				
		Edge e2;
		Edge e3;
};

inline std::ostream &operator << (std::ostream &str, const Triangle & t)
{
	return str << "Triangle:" << std::endl << "\t" << t.p1 << std::endl << "\t" << t.p2 << std::endl << "\t" << t.p3 << std::endl << "\t" << t.e1 << std::endl << "\t" << t.e2 << std::endl << "\t" << t.e3 << std::endl;
		
}

inline bool operator == (const Triangle &t1, const Triangle &t2)
{
	return	(t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) &&
			(t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) && 
			(t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3);
}


#endif
