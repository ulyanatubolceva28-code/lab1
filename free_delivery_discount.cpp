#include "free_delivery_discount.h"

#include "logging_proxy.h"
#include "order.h"

#include <string>

namespace lab2 {

void FreeDeliveryDiscount::apply(Order& order) const {
    const std::string name = getName();

    if (order.hasPromotion(name)) {
        return;
    }

    order.setFreeDelivery(true);
    order.addPromotion(name);

    LoggingProxy::log(LogSource::Discount, name);
}

std::string FreeDeliveryDiscount::getName() const {
    return "Бесплатная доставка";
}

}