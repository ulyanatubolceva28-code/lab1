#pragma once

#include "order.h"

#include <chrono>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace lab2 {

class IOrderService {
public:
    virtual ~IOrderService() = default;

    virtual std::shared_ptr<Order> createOrder(
        const std::string& clientId,
        const std::string& region,
        const std::vector<Product>& products,
        std::shared_ptr<DeliveryStrategy> delivery
    ) = 0;

    virtual double getTurnover(
        std::chrono::system_clock::time_point from,
        std::chrono::system_clock::time_point to
    ) const = 0;

    virtual std::size_t getUniqueClientsCount() const = 0;
};

}