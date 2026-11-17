#pragma once

#include "delivery_strategy.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace lab2 {

class DeliveryProxy final : public DeliveryStrategy {
public:
    explicit DeliveryProxy(std::shared_ptr<DeliveryStrategy> realDelivery);

    double getCost(const Order& order) const override;
    std::string getEstimatedTime() const override;
    bool isAvailable(const Order& order) const override;
    double getMaxWeight() const override;
    std::string getName() const override;

private:
    std::string makeCacheKey(const Order& order) const;

    std::shared_ptr<DeliveryStrategy> realDelivery_;
    mutable std::unordered_map<std::string, double> costCache_;
};

}