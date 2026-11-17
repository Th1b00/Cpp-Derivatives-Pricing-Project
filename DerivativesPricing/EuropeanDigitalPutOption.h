#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    using EuropeanDigitalOption::EuropeanDigitalOption;
    double payoff(double price) const override;
    optionType GetOptionType() const override;
};
