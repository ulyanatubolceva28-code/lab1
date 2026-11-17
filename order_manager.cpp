#include "order_manager.h"

#include "logging_proxy.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

namespace lab2 {

OrderManager::OrderManager(std::size_t maxActiveOrders)
    : maxActiveOrders_(maxActiveOrders),
      nextOrderId_(1) {
    if (maxActiveOrders_ == 0) {
        throw std::invalid_argument("Лимит активных заказов должен быть больше нуля");
    }
}

OrderManager::~OrderManager() {
    for (const std::shared_ptr<Order>& order : orders_) {
        order->detachObserver(this);
    }
}

std::shared_ptr<Order> OrderManager::createOrder(
    const std::string& clientId,
    const std::string& region,
    const std::vector<Product>& products,
    std::shared_ptr<DeliveryStrategy> delivery
) {
    if (!delivery) {
        throw std::invalid_argument("Для создания заказа нужно выбрать доставку");
    }

    if (getActiveOrderCount(clientId) >= maxActiveOrders_) {
        throw std::runtime_error("Клиент достиг лимита активных заказов");
    }

    auto order = std::make_shared<Order>(
        nextOrderId_,
        clientId,
        region,
        products,
        std::move(delivery)
    );

    orders_.push_back(order);
    order->attachObserver(this);
    ++nextOrderId_;

    LoggingProxy::log(
        LogSource::Manager,
        "Создан заказ #" + std::to_string(order->getId())
    );

    return order;
}

bool OrderManager::contributesToTurnover(OrderStatus status) noexcept {
    return status == OrderStatus::Paid ||
           status == OrderStatus::Shipped ||
           status == OrderStatus::Delivered;
}

double OrderManager::getTurnover(
    std::chrono::system_clock::time_point from,
    std::chrono::system_clock::time_point to
) const {
    if (from > to) {
        throw std::invalid_argument("Начало периода не может быть позже его конца");
    }

    double total = 0.0;

    for (const std::shared_ptr<Order>& order : orders_) {
        const auto createdAt = order->getCreatedAt();

        if (createdAt < from || createdAt > to) {
            continue;
        }

        if (contributesToTurnover(order->getStatus())) {
            total += order->getTotalCost();
        }
    }

    return total;
}

std::size_t OrderManager::getUniqueClientsCount() const {
    std::unordered_set<std::string> clients;

    for (const std::shared_ptr<Order>& order : orders_) {
        clients.insert(order->getClientId());
    }

    return clients.size();
}

std::size_t OrderManager::getActiveOrderCount(
    const std::string& clientId
) const {
    return static_cast<std::size_t>(
        std::count_if(
            orders_.begin(),
            orders_.end(),
            [&clientId](const std::shared_ptr<Order>& order) {
                return order->getClientId() == clientId && order->isActive();
            }
        )
    );
}

std::size_t OrderManager::getOrderCount() const noexcept {
    return orders_.size();
}

void OrderManager::onOrderEvent(const OrderEvent& event) {
    LoggingProxy::log(
        LogSource::Order,
        "Заказ #" +
            std::to_string(event.orderId) +
            ": " +
            toString(event.oldStatus) +
            " -> " +
            toString(event.newStatus)
    );
}

}