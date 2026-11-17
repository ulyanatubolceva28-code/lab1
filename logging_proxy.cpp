#include "logging_proxy.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace lab2 {

LoggingProxy::LoggingProxy(std::shared_ptr<IOrderService> target)
    : target_(std::move(target)) {
    if (!target_) {
        throw std::invalid_argument("Целевой объект прокси не может быть пустым");
    }
}

std::shared_ptr<Order> LoggingProxy::createOrder(
    const std::string& clientId,
    const std::string& region,
    const std::vector<Product>& products,
    std::shared_ptr<DeliveryStrategy> delivery
) {
    log(LogSource::Manager, "Запрос на создание заказа");

    try {
        auto order = target_->createOrder(
            clientId,
            region,
            products,
            std::move(delivery)
        );

        log(
            LogSource::Manager,
            "Заказ #" + std::to_string(order->getId()) + " создан"
        );

        return order;
    } catch (const std::exception& exception) {
        log(
            LogSource::Manager,
            "Не удалось создать заказ: " + std::string(exception.what())
        );
        throw;
    }
}

double LoggingProxy::getTurnover(
    std::chrono::system_clock::time_point from,
    std::chrono::system_clock::time_point to
) const {
    log(LogSource::Manager, "Запрос оборота за период");
    return target_->getTurnover(from, to);
}

std::size_t LoggingProxy::getUniqueClientsCount() const {
    log(LogSource::Manager, "Запрос количества уникальных клиентов");
    return target_->getUniqueClientsCount();
}

void LoggingProxy::log(LogSource source, const std::string& message) {
    const char* label = "GENERAL";

    switch (source) {
        case LogSource::Order:
            label = "ORDER";
            break;
        case LogSource::Delivery:
            label = "DELIVERY";
            break;
        case LogSource::Discount:
            label = "DISCOUNT";
            break;
        case LogSource::Manager:
            label = "MANAGER";
            break;
    }

    std::cout << '[' << label << "] " << message << '\n';
}

}