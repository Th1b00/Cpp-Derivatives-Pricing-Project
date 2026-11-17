#include "CRRPricer.h"

#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up,
                     double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up),
      _down(down), _interest_rate(interest_rate), _q(0.0), _tree(depth),
      _computed(false) {
    if (_option == nullptr) throw std::invalid_argument("Option must not be null");
    if (depth < 0) throw std::invalid_argument("Depth must be nonnegative");
    if (!(asset_price > 0.0) || !std::isfinite(asset_price))
        throw std::invalid_argument("Asset price must be positive and finite");
    if (!std::isfinite(up) || !std::isfinite(down) || !(up > down) || !(down > -1.0))
        throw std::invalid_argument("Require U > D > -1");
    if (!std::isfinite(interest_rate) || !(down < interest_rate && interest_rate < up))
        throw std::invalid_argument("Arbitrage condition violated: require D < R < U");
    _q = (interest_rate - down) / (up - down);
}

double CRRPricer::assetAt(int n, int i) const {
    return _asset_price * std::pow(1.0 + _up, i) * std::pow(1.0 + _down, n - i);
}

void CRRPricer::compute() {
    for (int i = 0; i <= _depth; ++i)
        _tree.setNode(_depth, i, _option->payoff(assetAt(_depth, i)));
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            const double value = (_q * _tree.getNode(n + 1, i + 1)
                + (1.0 - _q) * _tree.getNode(n + 1, i)) / (1.0 + _interest_rate);
            _tree.setNode(n, i, value);
        }
    }
    _computed = true;
}

double CRRPricer::get(int n, int i) const {
    if (!_computed) throw std::logic_error("CRR tree has not been computed");
    return _tree.getNode(n, i);
}

double CRRPricer::closedFormPrice() const {
    double probability = std::pow(1.0 - _q, _depth);
    double expectation = 0.0;
    for (int i = 0; i <= _depth; ++i) {
        expectation += probability * _option->payoff(assetAt(_depth, i));
        if (i < _depth) {
            probability *= (static_cast<double>(_depth - i) / (i + 1))
                * (_q / (1.0 - _q));
        }
    }
    return expectation / std::pow(1.0 + _interest_rate, _depth);
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) return closedFormPrice();
    if (!_computed) compute();
    return _tree.getNode(0, 0);
}
