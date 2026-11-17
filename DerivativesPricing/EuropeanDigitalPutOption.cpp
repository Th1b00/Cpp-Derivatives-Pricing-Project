#include "EuropeanDigitalPutOption.h"

double EuropeanDigitalPutOption::payoff(double price) const {
    return price <= getDigitalStrike() ? 1.0 : 0.0;
}

optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::put;
}
