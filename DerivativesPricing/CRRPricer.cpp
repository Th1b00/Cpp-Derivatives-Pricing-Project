#include "CRRPricer.h"

#include <cmath>
#include <stdexcept>

using namespace std;

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up,
    double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up),
    _down(down), _interest_rate(interest_rate), _q(0.0), _tree(depth),
    _exercise(depth), _computed(false) {
    if (_option == nullptr) throw invalid_argument("Option must not be null");
    if (_option->isAsianOption())
        throw invalid_argument("CRRPricer cannot price Asian options");
    if (depth < 0) throw invalid_argument("Depth must be nonnegative");
    if (asset_price <= 0.0 || !isfinite(asset_price))
        throw invalid_argument("Asset price must be positive and finite");
    if (!isfinite(up) || !isfinite(down) || up <= down || down <= -1.0)
        throw invalid_argument("Require U > D > -1");
    if (!isfinite(interest_rate) || interest_rate <= down || interest_rate >= up)
        throw invalid_argument("Arbitrage condition violated: require D < R < U");
    _q = (interest_rate - down) / (up - down);
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r,
    double volatility)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(0.0),
    _down(0.0), _interest_rate(0.0), _q(0.0), _tree(depth),
    _exercise(depth), _computed(false) {
    if (_option == nullptr) throw invalid_argument("Option must not be null");
    if (_option->isAsianOption())
        throw invalid_argument("CRRPricer cannot price Asian options");
    if (depth <= 0) throw invalid_argument("Depth must be positive");
    if (asset_price <= 0.0 || !isfinite(asset_price))
        throw invalid_argument("Asset price must be positive and finite");
    if (volatility < 0.0) throw invalid_argument("Volatility must be nonnegative");

    double h = _option->getExpiry() / depth;
    double drift = (r + 0.5 * volatility * volatility) * h;
    _up = exp(drift + volatility * sqrt(h)) - 1.0;
    _down = exp(drift - volatility * sqrt(h)) - 1.0;
    _interest_rate = exp(r * h) - 1.0;

    if (_down >= _interest_rate || _interest_rate >= _up)
        throw invalid_argument("Arbitrage condition violated: require D < R < U");
    _q = (_interest_rate - _down) / (_up - _down);
}

double CRRPricer::assetAt(int n, int i) const {
    return _asset_price * pow(1.0 + _up, i) * pow(1.0 + _down, n - i);
}

void CRRPricer::compute() {
    bool american = _option->isAmericanOption();

    for (int i = 0; i <= _depth; ++i) {
        double value = _option->payoff(assetAt(_depth, i));
        _tree.setNode(_depth, i, value);
        _exercise.setNode(_depth, i, american && value > 0.0);
    }

    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double continuation = (_q * _tree.getNode(n + 1, i + 1)
                + (1.0 - _q) * _tree.getNode(n + 1, i)) / (1.0 + _interest_rate);

            if (american) {
                double intrinsic = _option->payoff(assetAt(n, i));
                bool exercise = intrinsic >= continuation;
                _exercise.setNode(n, i, exercise);
                if (exercise)
                    _tree.setNode(n, i, intrinsic);
                else
                    _tree.setNode(n, i, continuation);
            }
            else {
                _exercise.setNode(n, i, false);
                _tree.setNode(n, i, continuation);
            }
        }
    }
    _computed = true;
}

double CRRPricer::get(int n, int i) const {
    if (_computed == false) throw logic_error("CRR tree has not been computed");
    return _tree.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) const {
    if (_computed == false) throw logic_error("CRR tree has not been computed");
    return _exercise.getNode(n, i);
}

double CRRPricer::closedFormPrice() const {
    double probability = pow(1.0 - _q, _depth);
    double expectation = 0.0;
    for (int i = 0; i <= _depth; ++i) {
        expectation += probability * _option->payoff(assetAt(_depth, i));
        if (i < _depth) {
            probability *= (static_cast<double>(_depth - i) / (i + 1))
                * (_q / (1.0 - _q));
        }
    }
    return expectation / pow(1.0 + _interest_rate, _depth);
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form && _option->isAmericanOption() == false) {
        return closedFormPrice();
    }
    if (_computed == false) {
        compute();
    }
    return _tree.getNode(0, 0);
}