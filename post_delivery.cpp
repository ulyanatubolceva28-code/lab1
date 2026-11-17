#include "post_delivery.h"

#include "order.h"
#include "region_validator.h"

namespace lab2 {

double PostDelivery::getCost(const Order&) const {
    return 200.0;
}

std::string PostDelivery::getEstimatedTime() const {
    return "5–10 дней";
}

bool PostDelivery::isAvailable(const Order& order) const {
    return RegionValidator::isSupportedRegion(order.getRegion()) &&
           order.getTotalWeight() <= getMaxWeight();
}

double PostDelivery::getMaxWeight() const {
    return 10.0;
}

std::string PostDelivery::getName() const {
    return "Почта";
}

}