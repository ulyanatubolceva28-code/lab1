#pragma once
#include <string>
#include <memory>
#include "attributes.h"

class Warehouse;

class Product {
private:
    static int nextId_;
    int id_;
    std::string name_;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category_;

protected:
    Product(const std::string& name, int price, int quantity, double weight, const std::string& category);
    Product(const Product& other);

public:
    virtual ~Product() = default;

    int getId() const;
    const std::string& getName() const;
    const Price& getPrice() const;
    const Quantity& getQuantity() const;
    const Weight& getWeight() const;
    const std::string& getCategory() const;

    void changeQuantity(int delta);
    void setPrice(const Price& newPrice);

    virtual std::unique_ptr<Product> clone() const = 0;
    virtual std::string toString() const;

    void transferTo(Warehouse& other);

    friend class Warehouse;
    friend class WarehouseIterator;
};

class Electronics : public Product {
protected:
    Electronics(const std::string& name, int price, int quantity, double weight);
    Electronics(const Electronics& other);
public:
    std::string toString() const override;
};

class Clothing : public Product {
protected:
    Clothing(const std::string& name, int price, int quantity, double weight);
    Clothing(const Clothing& other);
public:
    std::string toString() const override;
};

class Food : public Product {
protected:
    Food(const std::string& name, int price, int quantity, double weight);
    Food(const Food& other);
public:
    std::string toString() const override;
};