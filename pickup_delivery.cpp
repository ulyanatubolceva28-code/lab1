#include "pickup_delivery.h"

#include "order.h"
#include "region_validator.h"

#include <limits>

namespace lab2 {

double PickupDelivery::getCost(const Order&) const {
    return 0.0;
}

std::string PickupDelivery::getEstimatedTime() const {
    return "1–3 дня по графику выдачи";
}

bool PickupDelivery::isAvailable(const Order& order) const {
    return RegionValidator::isSupportedRegion(order.getRegion());
}

double PickupDelivery::getMaxWeight() const {
    return std::numeric_limits<double>::infinity();
}

std::string PickupDelivery::getName() const {
    return "Самовывоз";
}

}