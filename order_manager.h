#pragma once

#include "i_observer.h"
#include "i_order_service.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace lab2 {

class OrderManager final : public IOrderService, public IObserver {
public:
    explicit OrderManager(std::size_t maxActiveOrders = 5);
    ~OrderManager() override;

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
    std::size_t getActiveOrderCount(const std::string& clientId) const;
    std::size_t getOrderCount() const noexcept;

    void onOrderEvent(const OrderEvent& event) override;

private:
    static bool contributesToTurnover(OrderStatus status) noexcept;

    std::size_t maxActiveOrders_;
    int nextOrderId_;
    std::vector<std::shared_ptr<Order>> orders_;
};

}