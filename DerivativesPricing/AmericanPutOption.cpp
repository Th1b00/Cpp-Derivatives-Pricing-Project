#include "AmericanPutOption.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
    if (strike < 0.0) throw invalid_argument("Strike must be nonnegative");
}

double AmericanPutOption::payoff(double price) const {
    return max(_strike - price, 0.0);
}