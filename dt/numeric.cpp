#include "numeric.h"

bool almost_equal(const double x, const double y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) <= std::numeric_limits<double>::epsilon() * std::abs(x+y) * static_cast<double>(ulp)
    // unless the result is subnormal
        || std::abs(x-y) < std::numeric_limits<double>::min();
}

double half(const double x)
{
	return 0.5 * x;
}
