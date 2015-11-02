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
			_x = 0;
			_y = 0;
			_z = 0;
		}

		Vector3(T x, T y, T z) 
		{
			_x = x;
			_y = y;
			_z = z;	
		}

		Vector3(const Vector3 &v)
		{
			_x = v.getX();
			_y = v.getY();
			_z = v.getZ();
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

		T const & getZ() const
		{
			return _z;
		}

		void set(T x, T y, T z)
        {
            _x = x;
            _y = y;
			_z = z;
        }

        void setX(T x)
        {
            _x = x;
        }

        void setY(T y)
        {
            _y = y;
        }

		void setZ(T z)	
		{
			_z = z;
		}

		void set(Vector3<T> v)
		{
			_x = v.getX();
			_y = v.getY();
			_z = v.getZ();
		}

	private:
		T _x;
		T _y;
		T _z;
};

template<typename T>
std::ostream &operator << (std::ostream &str, Vector3<T> const &point) 
{
	return str << "Point x: " << point.getX() << " y: " << point.getY() << " z: " << point.getZ();
}
#endif

