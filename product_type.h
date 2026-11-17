#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace lab2 {

class ProductType {
public:
    static std::shared_ptr<ProductType> getType(
        const std::string& name,
        const std::string& category,
        double baseWeight,
        double basePrice
    );

    static std::size_t poolSize();
    static void clearPool();

    const std::string& getName() const noexcept;
    const std::string& getCategory() const noexcept;
    double getBaseWeight() const noexcept;
    double getBasePrice() const noexcept;

private:
    ProductType(
        std::string name,
        std::string category,
        double baseWeight,
        double basePrice
    );

    static std::string makeKey(
        const std::string& name,
        const std::string& category,
        double baseWeight,
        double basePrice
    );

    std::string name_;
    std::string category_;
    double baseWeight_;
    double basePrice_;

    static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;
    static std::mutex poolMutex_;
};

}