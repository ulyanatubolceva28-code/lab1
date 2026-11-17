#include "courier_delivery.h"

#include "order.h"

namespace lab2 {

double CourierDelivery::getCost(const Order&) const {
    return 500.0;
}

std::string CourierDelivery::getEstimatedTime() const {
    return "1–2 дня";
}

bool CourierDelivery::isAvailable(const Order& order) const {
    const std::string& region = order.getRegion();

    const bool supportedCity =
        region == "Москва" ||
        region == "Санкт-Петербург" ||
        region == "Казань";

    return supportedCity && order.getTotalWeight() <= getMaxWeight();
}

double CourierDelivery::getMaxWeight() const {
    return 20.0;
}

std::string CourierDelivery::getName() const {
    return "Курьерская доставка";
}

}