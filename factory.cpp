#include "factory.h"

std::unique_ptr<Product> ProductFactory::createSmartphone(int id, std::string name, double price, int qty, double weight, int warranty, std::string os) {
    return std::make_unique<Smartphone>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), warranty, std::move(os));
}

std::unique_ptr<Product> ProductFactory::createLaptop(int id, std::string name, double price, int qty, double weight, int warranty, std::string cpu) {
    return std::make_unique<Laptop>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), warranty, std::move(cpu));
}

std::unique_ptr<Product> ProductFactory::createTShirt(int id, std::string name, double price, int qty, double weight, std::string material, std::string size) {
    return std::make_unique<TShirt>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), std::move(material), std::move(size));
}

std::unique_ptr<Product> ProductFactory::createJacket(int id, std::string name, double price, int qty, double weight, std::string material, bool waterproof) {
    return std::make_unique<Jacket>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), std::move(material), waterproof);
}

std::unique_ptr<Product> ProductFactory::createMilk(int id, std::string name, double price, int qty, double weight, int expDays, double fat) {
    return std::make_unique<Milk>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), expDays, fat);
}

std::unique_ptr<Product> ProductFactory::createBread(int id, std::string name, double price, int qty, double weight, int expDays, bool wholeGrain) {
    return std::make_unique<Bread>(id, std::move(name), Price(price), Quantity(qty), Weight(weight), expDays, wholeGrain);
}

std::unique_ptr<Product> ProductFactory::createProduct(ProductType type, int id, std::string name, double price, int qty, double weight) {
    switch (type) {
        case ProductType::Smartphone:
            return createSmartphone(id, name, price, qty, weight, 12, "Android");
        case ProductType::Laptop:
            return createLaptop(id, name, price, qty, weight, 24, "Intel Core i7");
        case ProductType::TShirt:
            return createTShirt(id, name, price, qty, weight, "Хлопок", "L");
        case ProductType::Jacket:
            return createJacket(id, name, price, qty, weight, "Мембрана", true);
        case ProductType::Milk:
            return createMilk(id, name, price, qty, weight, 7, 3.2);
        case ProductType::Bread:
            return createBread(id, name, price, qty, weight, 3, true);
    }
    throw std::invalid_argument("Неизвестный тип товара");
}