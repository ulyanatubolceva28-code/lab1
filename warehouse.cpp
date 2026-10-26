#include "warehouse.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

WarehouseIterator::WarehouseIterator(
    std::vector<std::unique_ptr<Product>>::iterator current,
    std::vector<std::unique_ptr<Product>>::iterator end)
    : current_(current), end_(end) {}

WarehouseIterator& WarehouseIterator::operator++() {
    ++current_;
    return *this;
}

WarehouseIterator WarehouseIterator::operator++(int) {
    WarehouseIterator tmp = *this;
    ++current_;
    return tmp;
}

Product& WarehouseIterator::operator*() const {
    return **current_;
}

bool WarehouseIterator::operator!=(const WarehouseIterator& other) const {
    return current_ != other.current_;
}

bool WarehouseIterator::operator==(const WarehouseIterator& other) const {
    return current_ == other.current_;
}

// Warehouse
Warehouse::Warehouse(size_t maxSize) : maxSize_(maxSize) {
    if (maxSize == 0) throw std::invalid_argument("Max size must be positive");
}

Warehouse::Warehouse(const Warehouse& other) : maxSize_(other.maxSize_) {
    products_.reserve(other.products_.size());
    for (const auto& p : other.products_) {
        products_.push_back(p->clone());
    }
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this != &other) {
        products_.clear();
        maxSize_ = other.maxSize_;
        products_.reserve(other.products_.size());
        for (const auto& p : other.products_) {
            products_.push_back(p->clone());
        }
    }
    return *this;
}

Warehouse::Warehouse(Warehouse&& other) noexcept
    : products_(std::move(other.products_)), maxSize_(other.maxSize_) {
    other.maxSize_ = 0;
}

Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this != &other) {
        products_ = std::move(other.products_);
        maxSize_ = other.maxSize_;
        other.maxSize_ = 0;
    }
    return *this;
}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (products_.size() >= maxSize_) {
        throw std::overflow_error("Warehouse is full");
    }
    products_.push_back(std::move(product));
}

void Warehouse::removeById(int id) {
    auto it = std::find_if(products_.begin(), products_.end(),
        [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });
    if (it != products_.end()) {
        products_.erase(it);
    } else {
        throw std::runtime_error("Product with id " + std::to_string(id) + " not found");
    }
}

void Warehouse::removeByIndex(size_t index) {
    if (index >= products_.size()) {
        throw std::out_of_range("Index out of range");
    }
    products_.erase(products_.begin() + index);
}

Product* Warehouse::findById(int id) const {
    for (const auto& p : products_) {
        if (p->getId() == id) return p.get();
    }
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) const {
    std::vector<Product*> result;
    for (const auto& p : products_) {
        if (p->getCategory() == category) result.push_back(p.get());
    }
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) const {
    std::vector<Product*> result;
    for (const auto& p : products_) {
        if (p->getPrice().getValue() == price.getValue()) result.push_back(p.get());
    }
    return result;
}

WarehouseIterator Warehouse::begin() {
    return WarehouseIterator(products_.begin(), products_.end());
}

WarehouseIterator Warehouse::end() {
    return WarehouseIterator(products_.end(), products_.end());
}

WarehouseIterator Warehouse::begin() const {
    auto& self = const_cast<std::vector<std::unique_ptr<Product>>&>(products_);
    return WarehouseIterator(self.begin(), self.end());
}

WarehouseIterator Warehouse::end() const {
    auto& self = const_cast<std::vector<std::unique_ptr<Product>>&>(products_);
    return WarehouseIterator(self.end(), self.end());
}

size_t Warehouse::getSize() const {
    return products_.size();
}

size_t Warehouse::getMaxSize() const {
    return maxSize_;
}

void Warehouse::printAll() const {
    std::cout << "=== Warehouse (" << getSize() << "/" << getMaxSize() << ") ===" << std::endl;
    for (const auto& p : products_) {
        std::cout << p->toString() << std::endl;
    }
    std::cout << "========================================" << std::endl;
}