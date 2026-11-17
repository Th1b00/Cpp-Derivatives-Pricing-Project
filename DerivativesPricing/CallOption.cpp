#include "CallOption.h"
#include <algorithm>

double CallOption::payoff(double price) const {
    return std::max(price - getStrike(), 0.0);
}

optionType CallOption::GetOptionType() const {
    return optionType::call;
}
