#pragma once

#include "i_order_service.h"
#include "log_source.h"

#include <cstddef>
#include <memory>
#include <string>

namespace lab2 {

class LoggingProxy final : public IOrderService {
public:
    explicit LoggingProxy(std::shared_ptr<IOrderService> target);

    std::shared_ptr<Order> createOrder(
        const std::string& clientId,
        const std::string& region,
        const std::vector<Product>& products,
        std::shared_ptr<DeliveryStrategy> delivery
    ) override;

    double getTurnover(
        std::chrono::system_clock::time_point from,
        std::chrono::system_clock::time_point to
    ) const override;

    std::size_t getUniqueClientsCount() const override;

    static void log(LogSource source, const std::string& message);

private:
    std::shared_ptr<IOrderService> target_;
};

}