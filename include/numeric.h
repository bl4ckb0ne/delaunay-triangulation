#ifndef H_NUMERIC
#define H_NUMERIC

#include <math.h>
#include <limits>

namespace dt {

/**
 * @brief use of machine epsilon to compare floating-point values for equality
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
template<class T>
typename std::enable_if<std::is_floating_point_v<T>, bool>::type
almost_equal(T x, T y, int ulp=2)
{
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place)
	// unless the result is subnormal
	if constexpr (std::is_same_v<T, float>) {
		return fabsf(x-y) <= std::numeric_limits<float>::epsilon() * fabsf(x+y) * static_cast<float>(ulp)
				|| fabsf(x-y) < std::numeric_limits<float>::min();
	} else if constexpr (std::is_same_v<T, double>) {
		return fabs(x-y) <= std::numeric_limits<double>::epsilon() * fabs(x+y) * static_cast<double>(ulp)
				|| fabs(x-y) < std::numeric_limits<double>::min();
	}
}

template<typename T>
T half(const T x)
{
	if constexpr (std::is_same_v<T, float>) {
		return 0.5f * x;
	} else if constexpr (std::is_same_v<T, double>) {
		return 0.5 * x;
	}
	static_assert(true, "Must be floating-point type");
}

} // namespace dt

#endif
