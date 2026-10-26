#pragma once
#include "product.h"

class Smartphone : public Electronics {
private:
    std::string brand_;
public:
    Smartphone(int id, const std::string& name, int price, int quantity, double weight, const std::string& brand = "Generic");
    Smartphone(const Smartphone& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};

class Laptop : public Electronics {
private:
    int ramGB_;
public:
    Laptop(int id, const std::string& name, int price, int quantity, double weight, int ramGB = 8);
    Laptop(const Laptop& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};

class TShirt : public Clothing {
private:
    std::string size_;
public:
    TShirt(int id, const std::string& name, int price, int quantity, double weight, const std::string& size = "M");
    TShirt(const TShirt& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};

class Jacket : public Clothing {
private:
    std::string material_;
public:
    Jacket(int id, const std::string& name, int price, int quantity, double weight, const std::string& material = "Cotton");
    Jacket(const Jacket& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};

class Milk : public Food {
private:
    double fatPercent_;
public:
    Milk(int id, const std::string& name, int price, int quantity, double weight, double fatPercent = 2.5);
    Milk(const Milk& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};

class Bread : public Food {
private:
    std::string type_;
public:
    Bread(int id, const std::string& name, int price, int quantity, double weight, const std::string& type = "White");
    Bread(const Bread& other);
    std::unique_ptr<Product> clone() const override;
    std::string toString() const override;
};