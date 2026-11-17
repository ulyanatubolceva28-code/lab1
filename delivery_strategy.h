#pragma once

#include <memory>
#include <string>

namespace lab2 {

class Order;

class DeliveryStrategy : public std::enable_shared_from_this<DeliveryStrategy> {
public:
    virtual ~DeliveryStrategy() = default;

    virtual double getCost(const Order& order) const = 0;
    virtual std::string getEstimatedTime() const = 0;
    virtual bool isAvailable(const Order& order) const = 0;
    virtual double getMaxWeight() const = 0;
    virtual std::string getName() const = 0;
};

}