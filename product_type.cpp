#include "product_type.h"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace lab2 {

std::unordered_map<std::string, std::shared_ptr<ProductType>> ProductType::pool_;
std::mutex ProductType::poolMutex_;

ProductType::ProductType(
    std::string name,
    std::string category,
    double baseWeight,
    double basePrice
)
    : name_(std::move(name)),
      category_(std::move(category)),
      baseWeight_(baseWeight),
      basePrice_(basePrice) {
    if (name_.empty()) {
        throw std::invalid_argument("Название товара не может быть пустым");
    }

    if (category_.empty()) {
        throw std::invalid_argument("Категория товара не может быть пустой");
    }

    if (!std::isfinite(baseWeight_) || baseWeight_ < 0.0) {
        throw std::invalid_argument("Вес товара должен быть неотрицательным числом");
    }

    if (!std::isfinite(basePrice_) || basePrice_ < 0.0) {
        throw std::invalid_argument("Цена товара должна быть неотрицательным числом");
    }
}

std::string ProductType::makeKey(
    const std::string& name,
    const std::string& category,
    double baseWeight,
    double basePrice
) {
    std::ostringstream key;
    key << name << '\x1f'
        << category << '\x1f'
        << std::setprecision(17)
        << baseWeight << '\x1f'
        << basePrice;

    return key.str();
}

std::shared_ptr<ProductType> ProductType::getType(
    const std::string& name,
    const std::string& category,
    double baseWeight,
    double basePrice
) {
    const std::string key = makeKey(name, category, baseWeight, basePrice);

    std::lock_guard<std::mutex> lock(poolMutex_);

    const auto it = pool_.find(key);
    if (it != pool_.end()) {
        return it->second;
    }

    auto type = std::shared_ptr<ProductType>(
        new ProductType(name, category, baseWeight, basePrice)
    );

    pool_.emplace(key, type);
    return type;
}

std::size_t ProductType::poolSize() {
    std::lock_guard<std::mutex> lock(poolMutex_);
    return pool_.size();
}

void ProductType::clearPool() {
    std::lock_guard<std::mutex> lock(poolMutex_);
    pool_.clear();
}

const std::string& ProductType::getName() const noexcept {
    return name_;
}

const std::string& ProductType::getCategory() const noexcept {
    return category_;
}

double ProductType::getBaseWeight() const noexcept {
    return baseWeight_;
}

double ProductType::getBasePrice() const noexcept {
    return basePrice_;
}

}