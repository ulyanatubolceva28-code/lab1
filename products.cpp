#include "products.h"
#include <iomanip>

// Electronics
Electronics::Electronics(int id, std::string name, Price p, Quantity q, Weight w, int warranty)
    : Product(id, std::move(name), p, q, w), warrantyMonths_(warranty) {}

void Electronics::print() const {
    std::cout << "[Electronics] ID: " << id_ << " | " << name_ 
              << " | Цена: " << price_.getValue() << " | Кол-во: " << quantity_.getValue()
              << " | Вес: " << weight_.getValue() << " кг | Гарантия: " << warrantyMonths_ << " мес.";
}

Smartphone::Smartphone(int id, std::string name, Price p, Quantity q, Weight w, int warranty, std::string os)
    : Electronics(id, std::move(name), p, q, w, warranty), os_(std::move(os)) {}

std::unique_ptr<Product> Smartphone::clone() const {
    return std::make_unique<Smartphone>(id_, name_, price_, quantity_, weight_, warrantyMonths_, os_);
}

void Smartphone::print() const {
    Electronics::print();
    std::cout << " | OS: " << os_ << "\n";
}

Laptop::Laptop(int id, std::string name, Price p, Quantity q, Weight w, int warranty, std::string cpu)
    : Electronics(id, std::move(name), p, q, w, warranty), cpu_(std::move(cpu)) {}

std::unique_ptr<Product> Laptop::clone() const {
    return std::make_unique<Laptop>(id_, name_, price_, quantity_, weight_, warrantyMonths_, cpu_);
}

void Laptop::print() const {
    Electronics::print();
    std::cout << " | CPU: " << cpu_ << "\n";
}

// Clothing
Clothing::Clothing(int id, std::string name, Price p, Quantity q, Weight w, std::string material)
    : Product(id, std::move(name), p, q, w), material_(std::move(material)) {}

void Clothing::print() const {
    std::cout << "[Clothing] ID: " << id_ << " | " << name_ 
              << " | Цена: " << price_.getValue() << " | Кол-во: " << quantity_.getValue()
              << " | Вес: " << weight_.getValue() << " кг | Материал: " << material_;
}

TShirt::TShirt(int id, std::string name, Price p, Quantity q, Weight w, std::string material, std::string size)
    : Clothing(id, std::move(name), p, q, w, std::move(material)), size_(std::move(size)) {}

std::unique_ptr<Product> TShirt::clone() const {
    return std::make_unique<TShirt>(id_, name_, price_, quantity_, weight_, material_, size_);
}

void TShirt::print() const {
    Clothing::print();
    std::cout << " | Размер: " << size_ << "\n";
}

Jacket::Jacket(int id, std::string name, Price p, Quantity q, Weight w, std::string material, bool waterproof)
    : Clothing(id, std::move(name), p, q, w, std::move(material)), waterproof_(waterproof) {}

std::unique_ptr<Product> Jacket::clone() const {
    return std::make_unique<Jacket>(id_, name_, price_, quantity_, weight_, material_, waterproof_);
}

void Jacket::print() const {
    Clothing::print();
    std::cout << " | Водонепроницаемый: " << (waterproof_ ? "Да" : "Нет") << "\n";
}

// Food
Food::Food(int id, std::string name, Price p, Quantity q, Weight w, int expDays)
    : Product(id, std::move(name), p, q, w), expirationDays_(expDays) {}

void Food::print() const {
    std::cout << "[Food] ID: " << id_ << " | " << name_ 
              << " | Цена: " << price_.getValue() << " | Кол-во: " << quantity_.getValue()
              << " | Вес: " << weight_.getValue() << " кг | Годен дней: " << expirationDays_;
}

Milk::Milk(int id, std::string name, Price p, Quantity q, Weight w, int expDays, double fat)
    : Food(id, std::move(name), p, q, w, expDays), fatContent_(fat) {}

std::unique_ptr<Product> Milk::clone() const {
    return std::make_unique<Milk>(id_, name_, price_, quantity_, weight_, expirationDays_, fatContent_);
}

void Milk::print() const {
    Food::print();
    std::cout << " | Жирность: " << fatContent_ << "%\n";
}

Bread::Bread(int id, std::string name, Price p, Quantity q, Weight w, int expDays, bool wholeGrain)
    : Food(id, std::move(name), p, q, w, expDays), wholeGrain_(wholeGrain) {}

std::unique_ptr<Product> Bread::clone() const {
    return std::make_unique<Bread>(id_, name_, price_, quantity_, weight_, expirationDays_, wholeGrain_);
}

void Bread::print() const {
    Food::print();
    std::cout << " | Цельнозерновой: " << (wholeGrain_ ? "Да" : "Нет") << "\n";
}