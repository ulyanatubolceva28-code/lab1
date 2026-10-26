#pragma once
#include <stdexcept>

class Price {
private:
    int value_;
public:
    Price(int val);
    int getValue() const;
    void setValue(int newVal);
};

class Quantity {
private:
    int value_;
public:
    Quantity(int val);
    int getValue() const;
    void setValue(int newVal);
    void change(int delta);
};

class Weight {
private:
    double value_;
public:
    Weight(double val);
    double getValue() const;
    void setValue(double newVal);
};