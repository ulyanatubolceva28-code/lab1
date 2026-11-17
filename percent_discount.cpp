#include "percent_discount.h"

#include "logging_proxy.h"
#include "order.h"

#include <string>

namespace lab2 {

void PercentDiscount::apply(Order& order) const {
    const std::string name = getName();

    if (order.hasPromotion(name)) {
        return;
    }

    const double amount = order.getProductsTotal() * 0.10;

    order.addPriceDiscount(amount);
    order.addPromotion(name);

    LoggingProxy::log(
        LogSource::Discount,
        name + ": скидка " + std::to_string(amount) + " руб."
    );
}

std::string PercentDiscount::getName() const {
    return "Скидка 10%";
}

}