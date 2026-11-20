#include "AsianPutOption.h"
#include <algorithm>
#include <stdexcept>

AsianPutOption::AsianPutOption(std::vector<double> timeSteps, double strike)
    : AsianOption(std::move(timeSteps)), _strike(strike) {
    if (strike < 0.0) throw std::invalid_argument("Strike must be nonnegative");
}

double AsianPutOption::payoff(double price) const {
    return std::max(_strike - price, 0.0);
}
