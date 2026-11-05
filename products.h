#pragma once
#include "product.h"

//Электроника
class Electronics : public Product {
protected:
    int warrantyMonths_;
public:
    Electronics(int id, std::string name, Price p, Quantity q, Weight w, int warranty);
    void print() const override;
};

class Smartphone : public Electronics {
private:
    std::string os_;
public:
    Smartphone(int id, std::string name, Price p, Quantity q, Weight w, int warranty, std::string os);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};

class Laptop : public Electronics {
private:
    std::string cpu_;
public:
    Laptop(int id, std::string name, Price p, Quantity q, Weight w, int warranty, std::string cpu);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};

//Одежда
class Clothing : public Product {
protected:
    std::string material_;
public:
    Clothing(int id, std::string name, Price p, Quantity q, Weight w, std::string material);
    void print() const override;
};

class TShirt : public Clothing {
private:
    std::string size_;
public:
    TShirt(int id, std::string name, Price p, Quantity q, Weight w, std::string material, std::string size);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};

class Jacket : public Clothing {
private:
    bool waterproof_;
public:
    Jacket(int id, std::string name, Price p, Quantity q, Weight w, std::string material, bool waterproof);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};

//Продукты питания
class Food : public Product {
protected:
    int expirationDays_;
public:
    Food(int id, std::string name, Price p, Quantity q, Weight w, int expDays);
    void print() const override;
};

class Milk : public Food {
private:
    double fatContent_;
public:
    Milk(int id, std::string name, Price p, Quantity q, Weight w, int expDays, double fat);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};

class Bread : public Food {
private:
    bool wholeGrain_;
public:
    Bread(int id, std::string name, Price p, Quantity q, Weight w, int expDays, bool wholeGrain);
    std::unique_ptr<Product> clone() const override;
    void print() const override;
};