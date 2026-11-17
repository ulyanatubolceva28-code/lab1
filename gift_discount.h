#pragma once

#include "discount_strategy.h"
#include "order_product.h"

namespace lab2 {

class GiftDiscount final : public DiscountStrategy {
public:
    GiftDiscount();
    explicit GiftDiscount(Product gift);

    void apply(Order& order) const override;
    std::string getName() const override;

private:
    Product gift_;
};

}