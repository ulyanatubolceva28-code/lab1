#include "attributes.h"

// Price
Price::Price(int val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Price can't be negative");
}

int Price::getValue() const {
    return value_;
}

void Price::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Price can't be negative");
    value_ = newVal;
}

// Quantity
Quantity::Quantity(int val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Quantity can't be negative");
}

int Quantity::getValue() const {
    return value_;
}

void Quantity::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Quantity can't be negative");
    value_ = newVal;
}

void Quantity::change(int delta) {
    int newVal = value_ + delta;
    if (newVal < 0) throw std::invalid_argument("Quantity can't be negative after change");
    value_ = newVal;
}

// Weight
Weight::Weight(double val) : value_(val) {
    if (val < 0.0) throw std::invalid_argument("Weight can't be negative");
}

double Weight::getValue() const {
    return value_;
}

void Weight::setValue(double newVal) {
    if (newVal < 0.0) throw std::invalid_argument("Weight can't be negative");
    value_ = newVal;
}