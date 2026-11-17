#include "cashback_discount.h"
#include "courier_delivery.h"
#include "delivery_proxy.h"
#include "free_delivery_discount.h"
#include "gift_discount.h"
#include "logging_proxy.h"
#include "order.h"
#include "order_manager.h"
#include "order_product.h"
#include "percent_discount.h"
#include "pickup_delivery.h"
#include "post_delivery.h"
#include "product_type.h"

#include <chrono>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

using namespace lab2;

int main() {
    try {
        std::cout << "=== Сценарий 1. Легковес товаров ===\n";

        Product smartphone("Смартфон", "Электроника", 0.25, 90000.0, 1);
        Product sameSmartphone("Смартфон", "Электроника", 0.25, 90000.0, 1);
        Product laptop("Ноутбук", "Электроника", 3.0, 120000.0, 1);
        Product milk("Молоко", "Продукты", 1.0, 120.0, 1);
        Product heavyBox("Тяжёлая посылка", "Товары", 25.0, 10000.0, 1);
        Product book("Книга", "Книги", 0.5, 1500.0, 2);

        std::cout
            << "Объект типа смартфона общий: "
            << (smartphone.getType() == sameSmartphone.getType() ? "да" : "нет")
            << '\n';

        std::cout
            << "Типов товаров в пуле: "
            << ProductType::poolSize()
            << "\n\n";

        auto manager = std::make_shared<OrderManager>();
        LoggingProxy service(manager);

        auto courier = std::make_shared<DeliveryProxy>(
            std::make_shared<CourierDelivery>()
        );

        auto pickup = std::make_shared<DeliveryProxy>(
            std::make_shared<PickupDelivery>()
        );

        auto post = std::make_shared<DeliveryProxy>(
            std::make_shared<PostDelivery>()
        );

        std::cout << "=== Сценарий 2. Курьер и скидка 10% ===\n";

        auto courierOrder = service.createOrder(
            "client-1",
            "Москва",
            {smartphone, laptop},
            courier
        );

        PercentDiscount percentDiscount;
        *courierOrder + percentDiscount;

        courierOrder->setStatus(OrderStatus::Paid);
        courierOrder->setStatus(OrderStatus::Shipped);
        courierOrder->setStatus(OrderStatus::Delivered);

        std::cout << *courierOrder;

        Order copiedOrder(*courierOrder);

        std::cout
            << "Копия равна исходному заказу: "
            << (copiedOrder == *courierOrder ? "да" : "нет")
            << "\n\n";

        std::cout << "=== Сценарий 3. Самовывоз и акции ===\n";

        auto pickupOrder = service.createOrder(
            "client-2",
            "Казань",
            {heavyBox},
            pickup
        );

        *pickup << *pickupOrder;

        CashbackDiscount cashbackDiscount;
        GiftDiscount giftDiscount;

        *pickupOrder + cashbackDiscount;
        *pickupOrder + giftDiscount;
        pickupOrder->setStatus(OrderStatus::Paid);

        std::cout << *pickupOrder << '\n';

        std::cout << "=== Сценарий 4. Почта и бесплатная доставка ===\n";

        auto postOrder = service.createOrder(
            "client-3",
            "Владивосток",
            {book},
            post
        );

        FreeDeliveryDiscount freeDeliveryDiscount;
        *postOrder + freeDeliveryDiscount;
        postOrder->setStatus(OrderStatus::Paid);

        std::cout << *postOrder << '\n';

        try {
            service.createOrder(
                "client-heavy",
                "Москва",
                {heavyBox},
                courier
            );
        } catch (const std::exception& exception) {
            std::cout
                << "Ожидаемый отказ по весу: "
                << exception.what()
                << '\n';
        }

        try {
            service.createOrder(
                "client-region",
                "Марс",
                {milk},
                post
            );
        } catch (const std::exception& exception) {
            std::cout
                << "Ожидаемый отказ по региону: "
                << exception.what()
                << '\n';
        }

        std::cout << "\n=== Сценарий 5. Лимит, оборот и клиенты ===\n";

        std::vector<std::shared_ptr<Order>> activeOrders;

        for (int i = 0; i < 5; ++i) {
            activeOrders.push_back(
                service.createOrder(
                    "limit-client",
                    "Москва",
                    {milk},
                    courier
                )
            );
        }

        try {
            service.createOrder(
                "limit-client",
                "Москва",
                {milk},
                courier
            );
        } catch (const std::exception& exception) {
            std::cout
                << "Ожидаемый отказ по лимиту: "
                << exception.what()
                << '\n';
        }

        activeOrders.front()->setStatus(OrderStatus::Cancelled);

        auto orderAfterCancellation = service.createOrder(
            "limit-client",
            "Москва",
            {milk},
            courier
        );

        std::cout
            << "Активных заказов limit-client: "
            << manager->getActiveOrderCount("limit-client")
            << '\n';

        const auto now = std::chrono::system_clock::now();

        const double turnover = service.getTurnover(
            now - std::chrono::hours(1),
            now + std::chrono::hours(1)
        );

        std::cout << "Оборот за период: " << turnover << " руб.\n";

        std::cout
            << "Уникальных клиентов: "
            << service.getUniqueClientsCount()
            << '\n';

        std::cout
            << "Всего заказов: "
            << manager->getOrderCount()
            << '\n';

        std::cout
            << "Создан последний заказ: #"
            << orderAfterCancellation->getId()
            << '\n';
    } catch (const std::exception& exception) {
        std::cerr << "Ошибка: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}