#include "warehouse.h"
#include <algorithm>
#include <iostream>

// --- Итераторы ---
WarehouseIterator::WarehouseIterator(std::unique_ptr<Product>* ptr) : ptr_(ptr) {}
Product& WarehouseIterator::operator*() { return **ptr_; }
Product* WarehouseIterator::operator->() { return ptr_->get(); }
WarehouseIterator& WarehouseIterator::operator++() { ++ptr_; return *this; }
bool WarehouseIterator::operator!=(const WarehouseIterator& other) const { return ptr_ != other.ptr_; }
bool WarehouseIterator::operator==(const WarehouseIterator& other) const { return ptr_ == other.ptr_; }

ConstWarehouseIterator::ConstWarehouseIterator(const std::unique_ptr<Product>* ptr) : ptr_(ptr) {}
const Product& ConstWarehouseIterator::operator*() const { return **ptr_; }
const Product* ConstWarehouseIterator::operator->() const { return ptr_->get(); }
ConstWarehouseIterator& ConstWarehouseIterator::operator++() { ++ptr_; return *this; }
bool ConstWarehouseIterator::operator!=(const ConstWarehouseIterator& other) const { return ptr_ != other.ptr_; }
bool ConstWarehouseIterator::operator==(const ConstWarehouseIterator& other) const { return ptr_ == other.ptr_; }

// --- Склад ---
Warehouse::Warehouse(std::string name, size_t capacity) 
    : name_(std::move(name)), capacity_(capacity) {}

// Глубокое копирование с сохранением ID
Warehouse::Warehouse(const Warehouse& other) : name_(other.name_ + " (Copy)"), capacity_(other.capacity_) {
    products_.reserve(other.products_.size());
    for (const auto& item : other.products_) {
        auto cloned = item->clone();
        cloned->setOwner(this);
        products_.push_back(std::move(cloned));
    }
}

// Copy-and-Swap для гарантии безопасности исключений
Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this != &other) {
        Warehouse temp(other);
        *this = std::move(temp);
    }
    return *this;
}

// Конструктор перемещения
Warehouse::Warehouse(Warehouse&& other) noexcept
    : name_(std::move(other.name_)), capacity_(other.capacity_), products_(std::move(other.products_)) {
    for (auto& item : products_) {
        item->setOwner(this);
    }
    other.capacity_ = 0;
}

// Оператор присваивания перемещением
Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_);
        capacity_ = other.capacity_;
        products_ = std::move(other.products_);
        for (auto& item : products_) {
            item->setOwner(this);
        }
        other.capacity_ = 0;
    }
    return *this;
}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (!product) {
        throw std::invalid_argument("Попытка добавить nullptr");
    }
    if (products_.size() >= capacity_) {
        throw std::runtime_error("Склад '" + name_ + "' полон! Вместимость: " + std::to_string(capacity_));
    }
    product->setOwner(this);
    products_.push_back(std::move(product));
}

std::unique_ptr<Product> Warehouse::extractById(int id) {
    for (auto it = products_.begin(); it != products_.end(); ++it) {
        if ((*it)->getId() == id) {
            std::unique_ptr<Product> found = std::move(*it);
            products_.erase(it);
            found->setOwner(nullptr);
            return found;
        }
    }
    return nullptr;
}

bool Warehouse::removeById(int id) {
    auto item = extractById(id);
    return item != nullptr; // item безопасно уничтожается здесь
}

Product* Warehouse::findById(int id) const {
    for (const auto& item : products_) {
        if (item->getId() == id) {
            return item.get();
        }
    }
    return nullptr;
}

void Warehouse::transferProduct(int id, Warehouse& target) {
    if (this == &target) {
        throw std::invalid_argument("Нельзя перенести товар на тот же самый склад");
    }
    // Проверка лимита целевого склада ДО извлечения (Strong Exception Guarantee)
    if (target.isFull()) {
        throw std::runtime_error("Перенос невозможен: целевой склад '" + target.getName() + "' переполнен");
    }

    auto item = extractById(id);
    if (!item) {
        throw std::runtime_error("Товар с ID " + std::to_string(id) + " не найден на складе '" + name_ + "'");
    }
    target.addProduct(std::move(item));
}

size_t Warehouse::size() const { return products_.size(); }
size_t Warehouse::capacity() const { return capacity_; }
bool Warehouse::isFull() const { return products_.size() >= capacity_; }
std::string Warehouse::getName() const { return name_; }

void Warehouse::printAll() const {
    std::cout << "\n=== Склад: " << name_ << " (Занято: " << size() << "/" << capacity_ << ") ===\n";
    if (products_.empty()) {
        std::cout << "  [Склад пуст]\n";
        return;
    }
    for (const auto& item : products_) {
        std::cout << "  ";
        item->print();
    }
}

// Итераторы
WarehouseIterator Warehouse::begin() { return WarehouseIterator(products_.data()); }
WarehouseIterator Warehouse::end() { return WarehouseIterator(products_.data() + products_.size()); }
ConstWarehouseIterator Warehouse::begin() const { return ConstWarehouseIterator(products_.data()); }
ConstWarehouseIterator Warehouse::end() const { return ConstWarehouseIterator(products_.data() + products_.size()); }
ConstWarehouseIterator Warehouse::cbegin() const { return ConstWarehouseIterator(products_.data()); }
ConstWarehouseIterator Warehouse::cend() const { return ConstWarehouseIterator(products_.data() + products_.size()); }