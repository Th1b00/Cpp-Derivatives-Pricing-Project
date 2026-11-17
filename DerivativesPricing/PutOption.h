#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption {
public:
    using EuropeanVanillaOption::EuropeanVanillaOption;

    double payoff(double price) const override;
    optionType GetOptionType() const override;
};
