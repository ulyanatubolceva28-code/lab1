#include "product.h"
#include "warehouse.h"

int Product::nextId_ = 1;

Product::Product(int id, std::string name, Price price, Quantity quantity, Weight weight)
    : name_(std::move(name)), price_(price), quantity_(quantity), weight_(weight), owner_(nullptr) {
    if (id <= 0) {
        id_ = nextId_++;
    } else {
        id_ = id;
        if (id >= nextId_) {
            nextId_ = id + 1;
        }
    }
}

int Product::getId() const { return id_; }
std::string Product::getName() const { return name_; }
double Product::getPrice() const { return price_.getValue(); }
int Product::getQuantity() const { return quantity_.getValue(); }
double Product::getWeight() const { return weight_.getValue(); }

void Product::setOwner(Warehouse* owner) { owner_ = owner; }
Warehouse* Product::getOwner() const { return owner_; }

void Product::transferTo(Warehouse& target) {
    if (!owner_) {
        throw std::runtime_error("Товар с ID " + std::to_string(id_) + " не привязан к складу");
    }
    owner_->transferProduct(id_, target);
}