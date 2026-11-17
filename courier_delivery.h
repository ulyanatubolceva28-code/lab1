#pragma once

#include "delivery_strategy.h"

namespace lab2 {

class CourierDelivery final : public DeliveryStrategy {
public:
    double getCost(const Order& order) const override;
    std::string getEstimatedTime() const override;
    bool isAvailable(const Order& order) const override;
    double getMaxWeight() const override;
    std::string getName() const override;
};

}