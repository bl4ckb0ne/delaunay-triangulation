#include "vector2.h"

namespace dt {

template<typename T>
Vector2<T>::Vector2(const T vx, const T vy) :
	x(vx), y(vy)
{}

template<typename T>
T
Vector2<T>::dist2(const Vector2<T> &v) const
{
	const T dx = x - v.x;
	const T dy = y - v.y;
	return dx * dx + dy * dy;
}

template<>
float
Vector2<float>::dist(const Vector2<float> &v) const
{
	return hypotf(x - v.x, y - v.y);
}

template<>
double
Vector2<double>::dist(const Vector2<double> &v) const
{
	return hypot(x - v.x, y - v.y);
}

template<typename T>
T
Vector2<T>::norm2() const
{
	return x * x + y * y;
}

template<typename T>
bool
Vector2<T>::operator ==(const Vector2<T> &v) const
{
	return (this->x == v.x) && (this->y == v.y);
}

template<typename U>
std::ostream &
operator <<(std::ostream &str, const Vector2<U> &v)
{
	return str << "Point x: " << v.x << " y: " << v.y;
}

template struct Vector2<float>;
template struct Vector2<double>;

} // namespace dt
