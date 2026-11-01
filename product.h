#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "attributes.h"

class Warehouse;

class Product {
protected:
    static int nextId_;
    int id_;
    std::string name_;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    Warehouse* owner_;

public:
    Product(int id, std::string name, Price price, Quantity quantity, Weight weight);
    virtual ~Product() = default;

    virtual std::unique_ptr<Product> clone() const = 0;
    virtual void print() const = 0;

    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    double getWeight() const;

    void setOwner(Warehouse* owner);
    Warehouse* getOwner() const;

    void transferTo(Warehouse& target);
};