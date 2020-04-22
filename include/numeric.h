#ifndef H_NUMERIC
#define H_NUMERIC

#include <math.h>
#include <limits>
#include <type_traits>

namespace dt {

/**
 * @brief use of machine epsilon to compare floating-point values for equality
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
template<class T>
typename std::enable_if<std::is_same<T, float>::value, bool>::type
almost_equal(T x, T y, int ulp=2)
{
	return fabsf(x-y) <= std::numeric_limits<float>::epsilon() * fabsf(x+y) * static_cast<float>(ulp)
        	|| fabsf(x-y) < std::numeric_limits<float>::min();
}

template<class T>
typename std::enable_if<std::is_same<T, double>::value, bool>::type
almost_equal(T x, T y, int ulp=2)
{
	return fabs(x-y) <= std::numeric_limits<double>::epsilon() * fabs(x+y) * static_cast<double>(ulp)
	    	|| fabs(x-y) < std::numeric_limits<double>::min();
}

} // namespace dt

#endif
