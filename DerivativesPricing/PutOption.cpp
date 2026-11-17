#include "PutOption.h"
#include <algorithm>

double PutOption::payoff(double price) const {
    return std::max(getStrike() - price, 0.0);
}

optionType PutOption::GetOptionType() const {
    return optionType::put;
}
