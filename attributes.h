#pragma once
#include <stdexcept>
#include <iostream>

class Price {
private:
    double value_;
public:
    explicit Price(double val);
    double getValue() const;
    void setValue(double val);
};

class Quantity {
private:
    int value_;
public:
    explicit Quantity(int val);
    int getValue() const;
    void setValue(int val);
};

class Weight {
private:
    double value_;
public:
    explicit Weight(double val);
    double getValue() const;
    void setValue(double val);
};