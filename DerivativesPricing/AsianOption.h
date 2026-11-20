#pragma once
#include <vector>
#include "Option.h"

class AsianOption : public Option {
private:
    std::vector<double> _timeSteps;

public:
    explicit AsianOption(std::vector<double> timeSteps);
    std::vector<double> getTimeSteps() const;
    double payoffPath(const std::vector<double>& path) const final;
    bool isAsianOption() const override;
};
