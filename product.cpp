#include "product.h"
#include "warehouse.h"
#include <sstream>

int Product::nextId_ = 1;

Product::Product(const std::string& name, int price, int quantity, double weight, const std::string& category)
    : id_(nextId_++), name_(name), price_(price), quantity_(quantity), weight_(weight), category_(category) {}

Product::Product(const Product& other)
    : id_(nextId_++), name_(other.name_), price_(other.price_), quantity_(other.quantity_),
     weight_(other.weight_), category_(other.category_) {}

int Product::getId() const { return id_; }
const std::string& Product::getName() const { return name_; }
const Price& Product::getPrice() const { return price_; }
const Quantity& Product::getQuantity() const { return quantity_; }
const Weight& Product::getWeight() const { return weight_; }
const std::string& Product::getCategory() const { return category_; }

void Product::changeQuantity(int delta) {
    quantity_.change(delta);
}

void Product::setPrice(const Price& newPrice) {
    price_ = newPrice;
}

std::string Product::toString() const {
    std::ostringstream oss;
    oss << "ID:" << id_ << " | " << name_
        << " | Price:" << price_.getValue()
        << " | Qty:" << quantity_.getValue()
        << " | Weight:" << weight_.getValue()
        << " | Category:" << category_;
    return oss.str();
}

void Product::transferTo(Warehouse& other) {
    other.addProduct(this->clone());
}

// Electronics
Electronics::Electronics(const std::string& name, int price, int quantity, double weight)
    : Product(name, price, quantity, weight, "electronics") {}

Electronics::Electronics(const Electronics& other) : Product(other) {}

std::string Electronics::toString() const {
    return "[Electronics] " + Product::toString();
}

// Clothing
Clothing::Clothing(const std::string& name, int price, int quantity, double weight)
    : Product(name, price, quantity, weight, "clothing") {}

Clothing::Clothing(const Clothing& other) : Product(other) {}

std::string Clothing::toString() const {
    return "[Clothing] " + Product::toString();
}

// Food
Food::Food(const std::string& name, int price, int quantity, double weight)
    : Product(name, price, quantity, weight, "food") {}

Food::Food(const Food& other) : Product(other) {}

std::string Food::toString() const {
    return "[Food] " + Product::toString();
}