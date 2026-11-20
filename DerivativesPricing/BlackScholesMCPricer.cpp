#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price,
    double interest_rate, double volatility)
    : _option(option), _initial_price(initial_price), _interest_rate(interest_rate),
    _volatility(volatility), _nbPaths(0), _sum(0.0), _sumSquares(0.0) {
    if (_option == nullptr) throw std::invalid_argument("Option must not be null");
    if (!(initial_price > 0.0)) throw std::invalid_argument("Initial price must be positive");
    if (volatility < 0.0) throw std::invalid_argument("Volatility must be nonnegative");
}

int BlackScholesMCPricer::getNbPaths() const { return _nbPaths; }

void BlackScholesMCPricer::generate(int nb_paths) {
    if (nb_paths <= 0) throw std::invalid_argument("nb_paths must be positive");

    std::vector<double> times;
    if (_option->isAsianOption()) times = static_cast<AsianOption*>(_option)->getTimeSteps();
    else times.push_back(_option->getExpiry());

    const std::size_t m = times.size();
    const double discount = std::exp(-_interest_rate * _option->getExpiry());

    std::vector<double> drift(m), diffusion(m);
    double previous = 0.0;
    for (std::size_t k = 0; k < m; ++k) {
        const double dt = times[k] - previous;
        drift[k] = (_interest_rate - 0.5 * _volatility * _volatility) * dt;
        diffusion[k] = _volatility * std::sqrt(dt);
        previous = times[k];
    }

    std::vector<double> path(m);
    for (int p = 0; p < nb_paths; ++p) {
        double s = _initial_price;
        for (std::size_t k = 0; k < m; ++k) {
            s *= std::exp(drift[k] + diffusion[k] * MT::rand_norm());
            path[k] = s;
        }
        const double value = discount * _option->payoffPath(path);
        _sum += value;
        _sumSquares += value * value;
    }
    _nbPaths += nb_paths;
}

double BlackScholesMCPricer::operator()() const {
    if (_nbPaths == 0) throw std::logic_error("No path generated yet: price is undefined");
    return _sum / _nbPaths;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nbPaths < 2) throw std::logic_error("At least 2 paths are needed");
    const double n = static_cast<double>(_nbPaths);
    const double mean = _sum / n;
    double variance = (_sumSquares - n * mean * mean) / (n - 1.0);
    if (variance < 0.0) variance = 0.0;
    const double h = 1.96 * std::sqrt(variance / n);
    return { mean - h, mean + h };
}