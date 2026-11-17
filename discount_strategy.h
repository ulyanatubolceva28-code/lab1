#pragma once

#include <string>

namespace lab2 {

class Order;

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;

    virtual void apply(Order& order) const = 0;
    virtual std::string getName() const = 0;
};

}