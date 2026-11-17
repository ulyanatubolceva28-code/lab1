#include "delivery_proxy.h"

#include "logging_proxy.h"
#include "order.h"
#include "region_validator.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace lab2 {

DeliveryProxy::DeliveryProxy(std::shared_ptr<DeliveryStrategy> realDelivery)
    : realDelivery_(std::move(realDelivery)) {
    if (!realDelivery_) {
        throw std::invalid_argument("Стратегия доставки не может быть пустой");
    }
}

std::string DeliveryProxy::makeCacheKey(const Order& order) const {
    std::ostringstream key;
    key << realDelivery_->getName()
        << '|'
        << order.getRegion()
        << '|'
        << std::setprecision(17)
        << order.getTotalWeight();

    return key.str();
}

double DeliveryProxy::getCost(const Order& order) const {
    if (!isAvailable(order)) {
        throw std::runtime_error("Выбранный способ доставки недоступен");
    }

    const std::string key = makeCacheKey(order);
    const auto it = costCache_.find(key);

    if (it != costCache_.end()) {
        LoggingProxy::log(
            LogSource::Delivery,
            "Стоимость доставки получена из кэша"
        );
        return it->second;
    }

    const double cost = realDelivery_->getCost(order);
    costCache_.emplace(key, cost);

    LoggingProxy::log(
        LogSource::Delivery,
        "Стоимость доставки рассчитана: " + std::to_string(cost) + " руб."
    );

    return cost;
}

std::string DeliveryProxy::getEstimatedTime() const {
    return realDelivery_->getEstimatedTime();
}

bool DeliveryProxy::isAvailable(const Order& order) const {
    if (!RegionValidator::isSupportedRegion(order.getRegion())) {
        LoggingProxy::log(
            LogSource::Delivery,
            "Доставка отклонена: регион не поддерживается"
        );
        return false;
    }

    if (order.getTotalWeight() > realDelivery_->getMaxWeight()) {
        LoggingProxy::log(
            LogSource::Delivery,
            "Доставка отклонена: превышен допустимый вес"
        );
        return false;
    }

    const bool available = realDelivery_->isAvailable(order);

    LoggingProxy::log(
        LogSource::Delivery,
        available
            ? "Доставка доступна"
            : "Выбранная служба не доставляет в этот регион"
    );

    return available;
}

double DeliveryProxy::getMaxWeight() const {
    return realDelivery_->getMaxWeight();
}

std::string DeliveryProxy::getName() const {
    return realDelivery_->getName();
}

}