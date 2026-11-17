#include "EuropeanDigitalCallOption.h"

double EuropeanDigitalCallOption::payoff(double price) const {
    return price >= getDigitalStrike() ? 1.0 : 0.0;
}

optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::call;
}
