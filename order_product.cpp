#include "order_product.h"

#include <stdexcept>
#include <utility>

namespace lab2 {

Product::Product(
    std::string name,
    std::string category,
    double unitWeight,
    double unitPrice,
    int quantity
)
    : Product(
          ProductType::getType(name, category, unitWeight, unitPrice),
          quantity
      ) {
}

Product::Product(std::shared_ptr<ProductType> type, int quantity)
    : type_(std::move(type)),
      quantity_(quantity) {
    if (!type_) {
        throw std::invalid_argument("Тип товара не может быть пустым");
    }

    if (quantity_ <= 0) {
        throw std::invalid_argument("Количество товара должно быть больше нуля");
    }
}

const std::shared_ptr<ProductType>& Product::getType() const noexcept {
    return type_;
}

const std::string& Product::getName() const noexcept {
    return type_->getName();
}

const std::string& Product::getCategory() const noexcept {
    return type_->getCategory();
}

double Product::getUnitWeight() const noexcept {
    return type_->getBaseWeight();
}

double Product::getUnitPrice() const noexcept {
    return type_->getBasePrice();
}

int Product::getQuantity() const noexcept {
    return quantity_;
}

double Product::getTotalWeight() const noexcept {
    return getUnitWeight() * quantity_;
}

double Product::getTotalPrice() const noexcept {
    return getUnitPrice() * quantity_;
}

}