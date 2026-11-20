#include "AmericanCallOption.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
    if (strike < 0.0) throw invalid_argument("Strike must be nonnegative");
}

double AmericanCallOption::payoff(double price) const {
    return max(price - _strike, 0.0);
}