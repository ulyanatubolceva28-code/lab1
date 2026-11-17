#include "cashback_discount.h"

#include "logging_proxy.h"
#include "order.h"

#include <string>

namespace lab2 {

void CashbackDiscount::apply(Order& order) const {
    const std::string name = getName();

    if (order.hasPromotion(name)) {
        return;
    }

    const double cashback = order.getProductsTotal() * 0.05;

    order.addCashback(cashback);
    order.addPromotion(name);

    LoggingProxy::log(
        LogSource::Discount,
        name + ": начислено " + std::to_string(cashback) + " руб."
    );
}

std::string CashbackDiscount::getName() const {
    return "Кэшбэк 5%";
}

}