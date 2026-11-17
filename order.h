#pragma once

#include "delivery_strategy.h"
#include "i_observable.h"
#include "order_product.h"
#include "order_status.h"

#include <chrono>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace lab2 {

class DiscountStrategy;

class Order : public IObservable {
public:
    Order(
        int id,
        std::string clientId,
        std::string region,
        const std::vector<Product>& products,
        std::shared_ptr<DeliveryStrategy> delivery = nullptr
    );

    Order(const Order& other);
    Order& operator=(const Order& other);

    int getId() const noexcept;
    const std::string& getClientId() const noexcept;
    const std::string& getRegion() const noexcept;
    OrderStatus getStatus() const noexcept;

    const std::vector<Product>& getProducts() const noexcept;
    const std::vector<std::string>& getAppliedPromotions() const noexcept;
    const std::shared_ptr<DeliveryStrategy>& getDelivery() const noexcept;

    std::chrono::system_clock::time_point getCreatedAt() const noexcept;

    double getProductsTotal() const noexcept;
    double getTotalWeight() const noexcept;
    double getDiscountAmount() const noexcept;
    double getCashback() const noexcept;
    double getDeliveryCost() const;
    double getTotalCost() const;

    bool isFreeDelivery() const noexcept;
    bool isActive() const noexcept;
    bool hasPromotion(const std::string& promotion) const;

    void setStatus(OrderStatus status);
    void setDelivery(std::shared_ptr<DeliveryStrategy> delivery);

    void addPriceDiscount(double amount);
    void addCashback(double amount);
    void addPromotion(const std::string& promotion);
    void addGift(const Product& gift, const std::string& promotion);
    void setFreeDelivery(bool value);

private:
    static bool isAllowedTransition(
        OrderStatus from,
        OrderStatus to
    ) noexcept;

    void ensurePending() const;

    int id_;
    std::string clientId_;
    std::string region_;
    std::vector<Product> products_;
    std::shared_ptr<DeliveryStrategy> delivery_;
    OrderStatus status_;
    std::chrono::system_clock::time_point createdAt_;
    double discountAmount_;
    double cashback_;
    bool freeDelivery_;
    std::vector<std::string> appliedPromotions_;
};

Order& operator+(Order& order, const DiscountStrategy& discount);
Order& operator<<(DeliveryStrategy& delivery, Order& order);
std::ostream& operator<<(std::ostream& stream, const Order& order);
bool operator==(const Order& left, const Order& right) noexcept;

}