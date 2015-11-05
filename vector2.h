#ifndef H_VECTOR2
#define H_VECTOR2

#include <iostream>
#include <cmath>

template <typename T>
class Vector2
{
	public:
		//
		// Constructors
		//

		Vector2()
		{
			_x = 0;
			_y = 0;
		}

		Vector2(T x, T y) 
		{
			_x = x;
			_y = y;
		}

		Vector2(const Vector2 &v)
		{
			_x = v.getX();
			_y = v.getY();
		}

		//
		// Getters and setters
		//	
		T const & getX() const
        {
            return _x;
        }

        T const & getY() const 
        {
            return _y;
        }

		void set(const Vector2 &v)
		{
			_x = v.getX();
			_y = v.getY();
		}

		void set(T x, T y)
        {
            _x = x;
            _y = y;
        }

        void setX(T x)
        {
            _x = x;
        }

        void setY(T y)
        {
            _y = y;
        }

		void set(Vector2<T> v)
		{
			_x = v.getX();
			_y = v.getY();
		}

		//
		// Operations
		//	
		T dist2(const Vector2 &v)
		{
			T dx = _x - v.getX();
			T dy = _y - v.getY();
			return dx * dx + dy * dy;	
		}

		float dist(const Vector2 &v)
		{
			return sqrtf(dist2(v));
		}

		bool isInCircle(T cx, T cy, float r)
		{
			T dx = (cx - _x);
			T dy = (cy - _y);
			return ((dx * dx + dy * dy) <= (r * r));
		}	

	private:
		T _x;
		T _y;

};

template<typename T>
std::ostream &operator << (std::ostream &str, Vector2<T> const &point) 
{
	return str << "Point x: " << point.getX() << " y: " << point.getY();
}

template<typename T>
bool operator == (Vector2<T> v1, Vector2<T> v2)
{
	return (v1.getX() == v2.getX()) && (v1.getY() == v2.getY());
}
	
#endif
