#ifndef H_VECTOR2
#define H_VECTOR2

#include "numeric.h"

#include <iostream>
#include <cmath>
#include <type_traits>

namespace dt {

template<typename T>
struct Vector2
{
	using Type = T;
	Vector2() = default;
	Vector2(const Vector2<T> &v) = default;
	Vector2(Vector2<T>&&) = default;
	Vector2(const T vx, const T vy);

	T dist2(const Vector2<T> &v) const;
	T dist(const Vector2<T> &v) const;
	T norm2() const;

	Vector2 &operator=(const Vector2<T>&) = default;
	Vector2 &operator=(Vector2&&) = default;
	bool operator ==(const Vector2<T> &v) const;
	template<typename U>
	friend std::ostream &operator <<(std::ostream &str, const Vector2<U> &v);

	T x;
	T y;

	static_assert(std::is_floating_point_v<Vector2<T>::Type>,
		"Type must be floating-point");
};

template<typename T>
bool almost_equal(const Vector2<T> &v1, const Vector2<T> &v2)
{
	return almost_equal(v1.x, v2.x) && almost_equal(v1.y, v2.y);
}

} // namespace dt

#endif
