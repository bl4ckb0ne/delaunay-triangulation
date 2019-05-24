#ifndef H_NUMERIC
#define H_NUMERIC

#include <cmath>
#include <limits>

/**
 * @brief use of machine epsilon to compare floating-point values for equality
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
bool almost_equal(const double x, const double y, int ulp=2);

double half(const double x);

#endif
