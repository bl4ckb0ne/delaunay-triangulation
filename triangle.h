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
		Triangle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);
		Triangle(const Edge &e1, const Edge &e2, const Edge &e3);
  		
		Vec2f const & getP1() const { return _p1; } 
		Vec2f const & getP2() const { return _p2; }
		Vec2f const & getP3() const { return _p3; }
		Edge const & getE1() const { return _e1; } 
		Edge const & getE2() const { return _e2; }
		Edge const & getE3() const { return _e3; }
	
		Vec3f getSidesLength();		
		bool inCircumCircle(Vec2f &p);
		Vec3f getCircumCircle();
		Vec2f getCircumCenter();
		float getCircumRadius();		
		bool containsEdge(const Edge &e);
		bool containsVertex(const Vec2f &v);
		bool same(const Triangle &t);
	
	private:
		Vec2f _p1;
		Vec2f _p2;
		Vec2f _p3;
		Edge _e1;				
		Edge _e2;
		Edge _e3;
};

inline std::ostream &operator << (std::ostream &str, const Triangle & t)
{
	return str << "Triangle:" << std::endl <<  " " << t.getP1() << std::endl << " " << t.getP2() << std::endl << " " << t.getP3() << std::endl;
}


#endif
