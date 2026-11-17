#include "BlackScholesPricer.h"

#include <cmath>
#include <stdexcept>

namespace {
    constexpr double invSqrt2 = 0.70710678118654752440;
    constexpr double invSqrt2Pi = 0.39894228040143267794;
    double cdf(double x) { return 0.5 * std::erfc(-x * invSqrt2); }
    double pdf(double x) { return invSqrt2Pi * std::exp(-0.5 * x * x); }
    void validate(Option* option, double spot, double vol) {
        if (!option) throw std::invalid_argument("Option must not be null");
        if (!(spot > 0.0) || !std::isfinite(spot)) throw std::invalid_argument("Asset price must be positive and finite");
        if (vol < 0.0 || !std::isfinite(vol)) throw std::invalid_argument("Volatility must be nonnegative and finite");
    }
}

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double spot,
    double rate, double vol)
    : _option(option), _asset_price(spot), _interest_rate(rate), _volatility(vol) {
    validate(_option, spot, vol);
}

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double spot,
    double rate, double vol)
    : _option(option), _asset_price(spot), _interest_rate(rate), _volatility(vol) {
    validate(_option, spot, vol);
}

double BlackScholesPricer::operator()() const {
    const double t = _option->getExpiry();
    const double rate = _interest_rate;
    const double discount = std::exp(-rate * t);
    const auto* vanilla = dynamic_cast<const EuropeanVanillaOption*>(_option);
    const auto* digital = dynamic_cast<const EuropeanDigitalOption*>(_option);
    if (t == 0.0 || _volatility == 0.0) {
        const double forwardSpot = _asset_price * std::exp(rate * t);
        return discount * _option->payoff(forwardSpot);
    }
    const double rootT = std::sqrt(t);
    const double sigmaRootT = _volatility * rootT;
    double strike;
    if (vanilla) strike = vanilla->_strike;
    else if (digital) strike = digital->_strike;
    else throw std::invalid_argument("Unsupported option type");
    if (strike == 0.0) {
        if (vanilla) return vanilla->GetOptionType() == optionType::call ? _asset_price : 0.0;
        return digital->GetOptionType() == optionType::call ? discount : 0.0;
    }
    const double d1 = (std::log(_asset_price / strike) + (rate + 0.5 * _volatility * _volatility) * t) / sigmaRootT;
    const double d2 = d1 - sigmaRootT;
    if (vanilla) {
        if (vanilla->GetOptionType() == optionType::call)
            return _asset_price * cdf(d1) - strike * discount * cdf(d2);
        return strike * discount * cdf(-d2) - _asset_price * cdf(-d1);
    }
    if (digital->GetOptionType() == optionType::call) return discount * cdf(d2);
    return discount * cdf(-d2);
}

double BlackScholesPricer::delta() const {
    const double t = _option->getExpiry();
    const auto* vanilla = dynamic_cast<const EuropeanVanillaOption*>(_option);
    const auto* digital = dynamic_cast<const EuropeanDigitalOption*>(_option);
    if (t == 0.0 || _volatility == 0.0) return 0.0;
    double strike;
    if (vanilla) strike = vanilla->_strike;
    else if (digital) strike = digital->_strike;
    else throw std::invalid_argument("Unsupported option type");
    if (strike == 0.0) {
        if (vanilla) return vanilla->GetOptionType() == optionType::call ? 1.0 : 0.0;
        return 0.0;
    }
    const double sigmaRootT = _volatility * std::sqrt(t);
    const double d1 = (std::log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * t) / sigmaRootT;
    const double d2 = d1 - sigmaRootT;
    if (vanilla) return vanilla->GetOptionType() == optionType::call ? cdf(d1) : cdf(d1) - 1.0;
    const double scale = std::exp(-_interest_rate * t) * pdf(d2) / (_asset_price * sigmaRootT);
    return digital->GetOptionType() == optionType::call ? scale : -scale;
}
