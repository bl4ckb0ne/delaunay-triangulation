#ifndef H_VECTOR3
#define H_VECTOR3

#include <iostream>

template <typename T>
class Vector3
{
	public:
		//
		// Constructors
		//
		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(T _x, T _y, T _z) 
		{
			x = _x;
			y = _y;
			z = _z;	
		}

		Vector3(const Vector3 &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		void set(Vector3<T> v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		T x;
		T y;
		T z;
};

template<typename T>
std::ostream &operator << (std::ostream &str, Vector3<T> const &point) 
{
	return str << "Point x: " << point.x << " y: " << point.y << " z: " << point.z;
}
#endif

