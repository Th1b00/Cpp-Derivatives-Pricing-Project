#pragma once
class Option
{
    private:
        double _expiry;

    public:
        explicit Option(double expiry);
        double getExpiry() const;
        virtual double payoff(double price) const = 0;
};

