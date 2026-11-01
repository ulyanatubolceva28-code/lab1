#pragma once
#include <string>
#include <vector>
#include <memory>
#include "product.h"

// Неконстантный итератор
class WarehouseIterator {
private:
    std::unique_ptr<Product>* ptr_;
public:
    explicit WarehouseIterator(std::unique_ptr<Product>* ptr);
    Product& operator*();
    Product* operator->();
    WarehouseIterator& operator++();
    bool operator!=(const WarehouseIterator& other) const;
    bool operator==(const WarehouseIterator& other) const;
};

// Константный итератор (Const-safety)
class ConstWarehouseIterator {
private:
    const std::unique_ptr<Product>* ptr_;
public:
    explicit ConstWarehouseIterator(const std::unique_ptr<Product>* ptr);
    const Product& operator*() const;
    const Product* operator->() const;
    ConstWarehouseIterator& operator++();
    bool operator!=(const ConstWarehouseIterator& other) const;
    bool operator==(const ConstWarehouseIterator& other) const;
};

class Warehouse {
private:
    std::string name_;
    size_t capacity_;
    std::vector<std::unique_ptr<Product>> products_;

public:
    Warehouse(std::string name, size_t capacity);
    ~Warehouse() = default;

    // Правило пяти (Rule of Five)
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;

    void addProduct(std::unique_ptr<Product> product);
    std::unique_ptr<Product> extractById(int id);
    bool removeById(int id);
    Product* findById(int id) const;

    size_t size() const;
    size_t capacity() const;
    bool isFull() const;
    std::string getName() const;
    void printAll() const;

    void transferProduct(int id, Warehouse& target);

    // Поддержка Range-based for циклов
    WarehouseIterator begin();
    WarehouseIterator end();
    ConstWarehouseIterator begin() const;
    ConstWarehouseIterator end() const;
    ConstWarehouseIterator cbegin() const;
    ConstWarehouseIterator cend() const;
};