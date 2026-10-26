#include "factory.h"

std::unique_ptr<Product> SmartphoneFactory::createProduct(int id, const std::string& name,
                                                           int price, int quantity, double weight) {
    return std::make_unique<Smartphone>(id, name, price, quantity, weight);
}

std::unique_ptr<Product> LaptopFactory::createProduct(int id, const std::string& name,
                                                       int price, int quantity, double weight) {
    return std::make_unique<Laptop>(id, name, price, quantity, weight);
}

std::unique_ptr<Product> TShirtFactory::createProduct(int id, const std::string& name,
                                                       int price, int quantity, double weight) {
    return std::make_unique<TShirt>(id, name, price, quantity, weight);
}

std::unique_ptr<Product> JacketFactory::createProduct(int id, const std::string& name,
                                                       int price, int quantity, double weight) {
    return std::make_unique<Jacket>(id, name, price, quantity, weight);
}

std::unique_ptr<Product> MilkFactory::createProduct(int id, const std::string& name,
                                                     int price, int quantity, double weight) {
    return std::make_unique<Milk>(id, name, price, quantity, weight);
}

std::unique_ptr<Product> BreadFactory::createProduct(int id, const std::string& name,
                                                      int price, int quantity, double weight) {
    return std::make_unique<Bread>(id, name, price, quantity, weight);
}