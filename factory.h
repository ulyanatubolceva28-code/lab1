#pragma once
#include <memory>
#include <string>
#include "product.h"
#include "products.h"

class ProductFactory {
public:
    virtual std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                                    int price, int quantity, double weight) = 0;
    virtual ~ProductFactory() = default;
};

class SmartphoneFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};

class LaptopFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};

class TShirtFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};

class JacketFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};

class MilkFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};

class BreadFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                            int price, int quantity, double weight) override;
};