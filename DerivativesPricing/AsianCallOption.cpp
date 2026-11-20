#include "AsianCallOption.h"
#include <algorithm>
#include <stdexcept>

AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike)
    : AsianOption(std::move(timeSteps)), _strike(strike) {
    if (strike < 0.0) throw std::invalid_argument("Strike must be nonnegative");
}

double AsianCallOption::payoff(double price) const {
    return std::max(price - _strike, 0.0);
}
