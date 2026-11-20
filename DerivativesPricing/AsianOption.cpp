#include "AsianOption.h"
#include <stdexcept>

namespace {
    double expiryFromSteps(const std::vector<double>& steps) {
        if (steps.empty()) throw std::invalid_argument("Asian option needs at least one time step");
        double prev = 0.0;
        for (double t : steps) {
            if (!(t > prev)) throw std::invalid_argument("Time steps must be positive and strictly increasing");
            prev = t;
        }
        return steps.back();
    }
}

AsianOption::AsianOption(std::vector<double> timeSteps)
    : Option(expiryFromSteps(timeSteps)), _timeSteps(std::move(timeSteps)) {
}

std::vector<double> AsianOption::getTimeSteps() const { return _timeSteps; }

double AsianOption::payoffPath(const std::vector<double>& path) const {
    if (path.empty()) throw std::invalid_argument("Path must not be empty");
    double sum = 0.0;
    for (double s : path) sum += s;
    return payoff(sum / static_cast<double>(path.size()));
}

bool AsianOption::isAsianOption() const { return true; }