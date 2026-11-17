#include "gift_discount.h"

#include "logging_proxy.h"
#include "order.h"

#include <stdexcept>
#include <utility>

namespace lab2 {

GiftDiscount::GiftDiscount()
    : GiftDiscount(Product("Подарок", "Акции", 0.0, 0.0, 1)) {
}

GiftDiscount::GiftDiscount(Product gift)
    : gift_(std::move(gift)) {
    if (gift_.getUnitPrice() != 0.0) {
        throw std::invalid_argument("Цена подарка должна быть равна нулю");
    }
}

void GiftDiscount::apply(Order& order) const {
    const std::string name = getName();

    if (order.hasPromotion(name)) {
        return;
    }

    order.addGift(gift_, name);
    LoggingProxy::log(LogSource::Discount, name);
}

std::string GiftDiscount::getName() const {
    return "Подарок к заказу";
}

}