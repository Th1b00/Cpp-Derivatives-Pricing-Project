#pragma once
#include "Option.h"

class AmericanOption : public Option {
public:
    explicit AmericanOption(double expiry);
    bool isAmericanOption() const override;
};
