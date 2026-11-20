#include "AmericanOption.h"
#include <stdexcept>

using namespace std;

AmericanOption::AmericanOption(double expiry) : Option(expiry) {
    if (expiry < 0.0) throw invalid_argument("Expiry must be nonnegative");
}

bool AmericanOption::isAmericanOption() const { return true; }