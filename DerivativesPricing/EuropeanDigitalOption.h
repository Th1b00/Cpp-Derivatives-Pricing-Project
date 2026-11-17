#pragma once

#include "EuropeanVanillaOption.h"

class BlackScholesPricer;

class EuropeanDigitalOption : public Option {
private:
    double _strike;

public:
    friend class BlackScholesPricer;

protected:
    double getDigitalStrike() const { return _strike; }

    EuropeanDigitalOption(double expiry, double strike);
    virtual optionType GetOptionType() const = 0;
};
