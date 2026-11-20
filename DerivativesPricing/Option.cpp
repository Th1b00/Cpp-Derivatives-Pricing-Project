#include "Option.h"
#include <stdexcept>
Option::Option(double expiry) : _expiry(expiry) {}

double Option::getExpiry() const {
    return _expiry;
}

double Option::payoffPath(const std::vector<double>& path) const {
    if (path.empty()) throw std::invalid_argument("Path must not be empty");
    return payoff(path.back());
}

bool Option::isAsianOption() const {
    return false;
}
