#pragma once
#include <vector>
#include "Option.h"

class BlackScholesMCPricer {
private:
    Option* _option;
    double _initial_price;
    double _interest_rate;
    double _volatility;
    int _nbPaths;
    double _sum;
    double _sumSquares;
public:
    BlackScholesMCPricer(Option* option, double initial_price,
        double interest_rate, double volatility);
    int getNbPaths() const;
    void generate(int nb_paths);
    double operator()() const;
    std::vector<double> confidenceInterval() const;
};