#pragma once
#include <vector>
#include <memory>
#include <string>
#include "product.h"

class WarehouseIterator {
private:
    std::vector<std::unique_ptr<Product>>::iterator current_;
    std::vector<std::unique_ptr<Product>>::iterator end_;
public:
    WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator current,
                      std::vector<std::unique_ptr<Product>>::iterator end);
    WarehouseIterator& operator++();
    WarehouseIterator operator++(int);
    Product& operator*() const;
    bool operator!=(const WarehouseIterator& other) const;
    bool operator==(const WarehouseIterator& other) const;
};

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;
public:
    Warehouse(size_t maxSize);
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;
    ~Warehouse() = default;

    void addProduct(std::unique_ptr<Product> product);
    void removeById(int id);
    void removeByIndex(size_t index);
    Product* findById(int id) const;
    std::vector<Product*> findByCategory(const std::string& category) const;
    std::vector<Product*> findByPrice(const Price& price) const;

    WarehouseIterator begin();
    WarehouseIterator end();
    WarehouseIterator begin() const;
    WarehouseIterator end() const;

    size_t getSize() const;
    size_t getMaxSize() const;
    void printAll() const;
};