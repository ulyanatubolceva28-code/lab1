#pragma once

#include "product_type.h"

#include <memory>
#include <string>

namespace lab2 {

class Product {
public:
    Product(
        std::string name,
        std::string category,
        double unitWeight,
        double unitPrice,
        int quantity
    );

    Product(std::shared_ptr<ProductType> type, int quantity);

    const std::shared_ptr<ProductType>& getType() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getCategory() const noexcept;

    double getUnitWeight() const noexcept;
    double getUnitPrice() const noexcept;
    int getQuantity() const noexcept;

    double getTotalWeight() const noexcept;
    double getTotalPrice() const noexcept;

private:
    std::shared_ptr<ProductType> type_;
    int quantity_;
};

}