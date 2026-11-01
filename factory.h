#pragma once
#include <memory>
#include <string>
#include "products.h"

enum class ProductType {
    Smartphone,
    Laptop,
    TShirt,
    Jacket,
    Milk,
    Bread
};

class ProductFactory {
public:
    static std::unique_ptr<Product> createSmartphone(int id, std::string name, double price, int qty, double weight, int warranty, std::string os);
    static std::unique_ptr<Product> createLaptop(int id, std::string name, double price, int qty, double weight, int warranty, std::string cpu);
    static std::unique_ptr<Product> createTShirt(int id, std::string name, double price, int qty, double weight, std::string material, std::string size);
    static std::unique_ptr<Product> createJacket(int id, std::string name, double price, int qty, double weight, std::string material, bool waterproof);
    static std::unique_ptr<Product> createMilk(int id, std::string name, double price, int qty, double weight, int expDays, double fat);
    static std::unique_ptr<Product> createBread(int id, std::string name, double price, int qty, double weight, int expDays, bool wholeGrain);

    // Универсальный метод
    static std::unique_ptr<Product> createProduct(ProductType type, int id, std::string name, double price, int qty, double weight);
};