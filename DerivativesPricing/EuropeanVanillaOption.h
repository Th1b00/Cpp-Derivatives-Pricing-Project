#pragma once

#include "Option.h"

enum class optionType { call, put };

class BlackScholesPricer;

class EuropeanVanillaOption : public Option {
private:
    double _strike;

protected:
    double getStrike() const;

public:
    friend class BlackScholesPricer;

    EuropeanVanillaOption(double expiry, double strike);
    virtual optionType GetOptionType() const = 0;
};


