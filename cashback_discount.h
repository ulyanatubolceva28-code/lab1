#pragma once

#include "discount_strategy.h"

namespace lab2 {

class CashbackDiscount final : public DiscountStrategy {
public:
    void apply(Order& order) const override;
    std::string getName() const override;
};

}