#include "order.h"

#include "discount_strategy.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace lab2 {

Order::Order(
    int id,
    std::string clientId,
    std::string region,
    const std::vector<Product>& products,
    std::shared_ptr<DeliveryStrategy> delivery
)
    : id_(id),
      clientId_(std::move(clientId)),
      region_(std::move(region)),
      products_(products),
      delivery_(nullptr),
      status_(OrderStatus::Pending),
      createdAt_(std::chrono::system_clock::now()),
      discountAmount_(0.0),
      cashback_(0.0),
      freeDelivery_(false) {
    if (id_ <= 0) {
        throw std::invalid_argument("ID заказа должен быть больше нуля");
    }

    if (clientId_.empty()) {
        throw std::invalid_argument("ID клиента не может быть пустым");
    }

    if (region_.empty()) {
        throw std::invalid_argument("Регион не может быть пустым");
    }

    if (products_.empty()) {
        throw std::invalid_argument("В заказе должен быть хотя бы один товар");
    }

    if (delivery) {
        setDelivery(std::move(delivery));
    }
}

Order::Order(const Order& other)
    : IObservable(other),
      id_(other.id_),
      clientId_(other.clientId_),
      region_(other.region_),
      products_(other.products_),
      delivery_(other.delivery_),
      status_(other.status_),
      createdAt_(other.createdAt_),
      discountAmount_(other.discountAmount_),
      cashback_(other.cashback_),
      freeDelivery_(other.freeDelivery_),
      appliedPromotions_(other.appliedPromotions_) {
}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        IObservable::operator=(other);

        id_ = other.id_;
        clientId_ = other.clientId_;
        region_ = other.region_;
        products_ = other.products_;
        delivery_ = other.delivery_;
        status_ = other.status_;
        createdAt_ = other.createdAt_;
        discountAmount_ = other.discountAmount_;
        cashback_ = other.cashback_;
        freeDelivery_ = other.freeDelivery_;
        appliedPromotions_ = other.appliedPromotions_;
    }

    return *this;
}

int Order::getId() const noexcept {
    return id_;
}

const std::string& Order::getClientId() const noexcept {
    return clientId_;
}

const std::string& Order::getRegion() const noexcept {
    return region_;
}

OrderStatus Order::getStatus() const noexcept {
    return status_;
}

const std::vector<Product>& Order::getProducts() const noexcept {
    return products_;
}

const std::vector<std::string>& Order::getAppliedPromotions() const noexcept {
    return appliedPromotions_;
}

const std::shared_ptr<DeliveryStrategy>& Order::getDelivery() const noexcept {
    return delivery_;
}

std::chrono::system_clock::time_point Order::getCreatedAt() const noexcept {
    return createdAt_;
}

double Order::getProductsTotal() const noexcept {
    double total = 0.0;

    for (const Product& product : products_) {
        total += product.getTotalPrice();
    }

    return total;
}

double Order::getTotalWeight() const noexcept {
    double total = 0.0;

    for (const Product& product : products_) {
        total += product.getTotalWeight();
    }

    return total;
}

double Order::getDiscountAmount() const noexcept {
    return discountAmount_;
}

double Order::getCashback() const noexcept {
    return cashback_;
}

double Order::getDeliveryCost() const {
    if (!delivery_) {
        throw std::logic_error("Для заказа не выбран способ доставки");
    }

    if (freeDelivery_) {
        return 0.0;
    }

    return delivery_->getCost(*this);
}

double Order::getTotalCost() const {
    const double productsCost = std::max(
        0.0,
        getProductsTotal() - discountAmount_
    );

    return productsCost + getDeliveryCost();
}

bool Order::isFreeDelivery() const noexcept {
    return freeDelivery_;
}

bool Order::isActive() const noexcept {
    return status_ == OrderStatus::Pending ||
           status_ == OrderStatus::Paid ||
           status_ == OrderStatus::Shipped;
}

bool Order::hasPromotion(const std::string& promotion) const {
    return std::find(
        appliedPromotions_.begin(),
        appliedPromotions_.end(),
        promotion
    ) != appliedPromotions_.end();
}

void Order::ensurePending() const {
    if (status_ != OrderStatus::Pending) {
        throw std::logic_error("Изменять заказ можно только в статусе pending");
    }
}

bool Order::isAllowedTransition(
    OrderStatus from,
    OrderStatus to
) noexcept {
    switch (from) {
        case OrderStatus::Pending:
            return to == OrderStatus::Paid ||
                   to == OrderStatus::Cancelled;

        case OrderStatus::Paid:
            return to == OrderStatus::Shipped ||
                   to == OrderStatus::Cancelled;

        case OrderStatus::Shipped:
            return to == OrderStatus::Delivered;

        case OrderStatus::Delivered:
        case OrderStatus::Cancelled:
            return false;
    }

    return false;
}

void Order::setStatus(OrderStatus status) {
    if (status == status_) {
        return;
    }

    if (!isAllowedTransition(status_, status)) {
        throw std::logic_error("Недопустимый переход статуса заказа");
    }

    const OrderStatus oldStatus = status_;
    status_ = status;

    notifyObservers({
        id_,
        oldStatus,
        status_,
        std::chrono::system_clock::now()
    });
}

void Order::setDelivery(std::shared_ptr<DeliveryStrategy> delivery) {
    ensurePending();

    if (!delivery) {
        throw std::invalid_argument("Способ доставки не может быть пустым");
    }

    if (!delivery->isAvailable(*this)) {
        throw std::runtime_error("Выбранный способ доставки недоступен");
    }

    delivery_ = std::move(delivery);
}

void Order::addPriceDiscount(double amount) {
    ensurePending();

    if (!std::isfinite(amount) || amount < 0.0) {
        throw std::invalid_argument("Размер скидки должен быть неотрицательным числом");
    }

    const double remaining = std::max(
        0.0,
        getProductsTotal() - discountAmount_
    );

    discountAmount_ += std::min(amount, remaining);
}

void Order::addCashback(double amount) {
    ensurePending();

    if (!std::isfinite(amount) || amount < 0.0) {
        throw std::invalid_argument("Размер кэшбэка должен быть неотрицательным числом");
    }

    cashback_ += amount;
}

void Order::addPromotion(const std::string& promotion) {
    ensurePending();

    if (promotion.empty()) {
        throw std::invalid_argument("Название акции не может быть пустым");
    }

    if (!hasPromotion(promotion)) {
        appliedPromotions_.push_back(promotion);
    }
}

void Order::addGift(const Product& gift, const std::string& promotion) {
    ensurePending();

    if (hasPromotion(promotion)) {
        return;
    }

    if (promotion.empty()) {
        throw std::invalid_argument("Название акции не может быть пустым");
    }

    if (gift.getUnitPrice() != 0.0) {
        throw std::invalid_argument("Цена подарка должна быть равна нулю");
    }

    products_.push_back(gift);
    addPromotion(promotion);
}

void Order::setFreeDelivery(bool value) {
    ensurePending();
    freeDelivery_ = value;
}

Order& operator+(Order& order, const DiscountStrategy& discount) {
    discount.apply(order);
    return order;
}

Order& operator<<(DeliveryStrategy& delivery, Order& order) {
    try {
        order.setDelivery(delivery.shared_from_this());
    } catch (const std::bad_weak_ptr&) {
        throw std::logic_error(
            "Для оператора << стратегию доставки нужно создать через shared_ptr"
        );
    }

    return order;
}

std::ostream& operator<<(std::ostream& stream, const Order& order) {
    std::ostringstream output;

    output << "Заказ #" << order.getId() << '\n'
           << "Клиент: " << order.getClientId() << '\n'
           << "Регион: " << order.getRegion() << '\n'
           << "Статус: " << toString(order.getStatus()) << '\n';

    if (order.getDelivery()) {
        output << "Доставка: " << order.getDelivery()->getName() << '\n'
               << "Срок: " << order.getDelivery()->getEstimatedTime() << '\n';
    } else {
        output << "Доставка: не выбрана\n";
    }

    output << "Товары:\n";

    for (const Product& product : order.getProducts()) {
        output << "  "
               << product.getName()
               << " x"
               << product.getQuantity()
               << " — "
               << std::fixed
               << std::setprecision(2)
               << product.getTotalPrice()
               << " руб.\n";
    }

    output << "Вес: "
           << std::fixed
           << std::setprecision(2)
           << order.getTotalWeight()
           << " кг\n"
           << "Сумма товаров: "
           << order.getProductsTotal()
           << " руб.\n"
           << "Скидка: "
           << order.getDiscountAmount()
           << " руб.\n"
           << "Кэшбэк: "
           << order.getCashback()
           << " руб.\n";

    if (order.getDelivery()) {
        output << "Стоимость доставки: "
               << order.getDeliveryCost()
               << " руб.\n"
               << "Итого: "
               << order.getTotalCost()
               << " руб.\n";
    } else {
        output << "Итого без доставки: "
               << std::max(
                      0.0,
                      order.getProductsTotal() - order.getDiscountAmount()
                  )
               << " руб.\n";
    }

    if (!order.getAppliedPromotions().empty()) {
        output << "Акции: ";

        for (std::size_t i = 0; i < order.getAppliedPromotions().size(); ++i) {
            if (i > 0) {
                output << ", ";
            }

            output << order.getAppliedPromotions()[i];
        }

        output << '\n';
    }

    return stream << output.str();
}

bool operator==(const Order& left, const Order& right) noexcept {
    return left.getId() == right.getId();
}

}