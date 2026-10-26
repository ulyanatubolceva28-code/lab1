#include "products.h"
#include <sstream>

// Smartphone
Smartphone::Smartphone(int id, const std::string& name, int price, int quantity, double weight, const std::string& brand)
    : Electronics(name, price, quantity, weight), brand_(brand) {}
Smartphone::Smartphone(const Smartphone& other) : Electronics(other), brand_(other.brand_) {}
std::unique_ptr<Product> Smartphone::clone() const { return std::make_unique<Smartphone>(*this); }
std::string Smartphone::toString() const { return Electronics::toString() + " | Brand:" + brand_; }

// Laptop
Laptop::Laptop(int id, const std::string& name, int price, int quantity, double weight, int ramGB)
    : Electronics(name, price, quantity, weight), ramGB_(ramGB) {}
Laptop::Laptop(const Laptop& other) : Electronics(other), ramGB_(other.ramGB_) {}
std::unique_ptr<Product> Laptop::clone() const { return std::make_unique<Laptop>(*this); }
std::string Laptop::toString() const { return Electronics::toString() + " | RAM:" + std::to_string(ramGB_) + "GB"; }

// TShirt
TShirt::TShirt(int id, const std::string& name, int price, int quantity, double weight, const std::string& size)
    : Clothing(name, price, quantity, weight), size_(size) {}
TShirt::TShirt(const TShirt& other) : Clothing(other), size_(other.size_) {}
std::unique_ptr<Product> TShirt::clone() const { return std::make_unique<TShirt>(*this); }
std::string TShirt::toString() const { return Clothing::toString() + " | Size:" + size_; }

// Jacket
Jacket::Jacket(int id, const std::string& name, int price, int quantity, double weight, const std::string& material)
    : Clothing(name, price, quantity, weight), material_(material) {}
Jacket::Jacket(const Jacket& other) : Clothing(other), material_(other.material_) {}
std::unique_ptr<Product> Jacket::clone() const { return std::make_unique<Jacket>(*this); }
std::string Jacket::toString() const { return Clothing::toString() + " | Material:" + material_; }

// Milk
Milk::Milk(int id, const std::string& name, int price, int quantity, double weight, double fatPercent)
    : Food(name, price, quantity, weight), fatPercent_(fatPercent) {}
Milk::Milk(const Milk& other) : Food(other), fatPercent_(other.fatPercent_) {}
std::unique_ptr<Product> Milk::clone() const { return std::make_unique<Milk>(*this); }
std::string Milk::toString() const { return Food::toString() + " | Fat:" + std::to_string(fatPercent_) + "%"; }

// Bread
Bread::Bread(int id, const std::string& name, int price, int quantity, double weight, const std::string& type)
    : Food(name, price, quantity, weight), type_(type) {}
Bread::Bread(const Bread& other) : Food(other), type_(other.type_) {}
std::unique_ptr<Product> Bread::clone() const { return std::make_unique<Bread>(*this); }
std::string Bread::toString() const { return Food::toString() + " | Type:" + type_; }