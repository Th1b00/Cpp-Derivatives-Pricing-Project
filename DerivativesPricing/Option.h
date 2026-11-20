#pragma once
#include <vector>
class Option
{
    private:
        double _expiry;

    public:
        explicit Option(double expiry);
        double getExpiry() const;
        virtual double payoff(double price) const = 0;
        virtual ~Option() = default;
        virtual double payoffPath(const std::vector<double>& path) const;
        virtual bool isAsianOption() const;
};

