#include "attributes.h"

Price::Price(double val) : value_(val) {
    if (val < 0.0) throw std::invalid_argument("Цена не может быть отрицательной");
}
double Price::getValue() const { return value_; }
void Price::setValue(double val) {
    if (val < 0.0) throw std::invalid_argument("Цена не может быть отрицательной");
    value_ = val;
}

Quantity::Quantity(int val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Количество не может быть отрицательным");
}
int Quantity::getValue() const { return value_; }
void Quantity::setValue(int val) {
    if (val < 0) throw std::invalid_argument("Количество не может быть отрицательным");
    value_ = val;
}

Weight::Weight(double val) : value_(val) {
    if (val < 0.0) throw std::invalid_argument("Вес не может быть отрицательным");
}
double Weight::getValue() const { return value_; }
void Weight::setValue(double val) {
    if (val < 0.0) throw std::invalid_argument("Вес не может быть отрицательным");
    value_ = val;
}