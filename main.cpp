#include <iostream>
#include "factory.h"
#include "warehouse.h"

int main() {
    try {
        std::cout << "========== 1. СОЗДАНИЕ СКЛАДОВ ==========\n";
        Warehouse whA("Главный Склад А", 5);
        Warehouse whB("Филиал Б", 3);

        // Сгенерированный ID
        std::cout << "\n========== 2. СОЗДАНИЕ ТОВАРОВ (FACTORY: ID АВТО / ВРУЧНУЮ) ==========\n";
        auto p1 = ProductFactory::createSmartphone(0, "iPhone 15", 999.99, 10, 0.2, 12, "iOS");
        auto p2 = ProductFactory::createLaptop(0, "MacBook Pro", 2499.00, 5, 1.5, 24, "M3 Pro");
        auto p3 = ProductFactory::createTShirt(0, "Polo", 45.0, 50, 0.25, "Хлопок", "M");

        // Явно переданный ID
        auto pExplicit = ProductFactory::createMilk(777, "Фермерское молоко", 2.5, 100, 1.0, 5, 3.8);

        std::cout << "Товар 1: ID = " << p1->getId() << " (сгенерирован автоматически)\n";
        std::cout << "Товар 2: ID = " << p2->getId() << " (сгенерирован автоматически)\n";
        std::cout << "Товар 3: ID = " << p3->getId() << " (сгенерирован автоматически)\n";
        std::cout << "Товар 4: ID = " << pExplicit->getId() << " (задан вручную: 777)\n";

        // Следующий авто-ID станет 778
        auto pAutoNext = ProductFactory::createBread(0, "Бородинский", 1.2, 30, 0.4, 4, false);
        std::cout << "Товар 5: ID = " << pAutoNext->getId() << " (автоматически после 777)\n";

        std::cout << "\n========== 3. ДОБАВЛЕНИЕ ТОВАРОВ НА СКЛАД ==========\n";
        whA.addProduct(std::move(p1));
        whA.addProduct(std::move(p2));
        whA.addProduct(std::move(p3));
        whA.addProduct(std::move(pExplicit));
        whA.addProduct(std::move(pAutoNext));

        whA.printAll();

        std::cout << "\n========== 4. ПРОВЕРКА ЛИМИТА ВМЕСТИМОСТИ ==========\n";
        try {
            auto overflowItem = ProductFactory::createBread(0, "Батон", 0.9, 10, 0.3, 2, false);
            whA.addProduct(std::move(overflowItem));
        } catch (const std::exception& e) {
            std::cout << "[Ожидаемый перехват ошибки]: " << e.what() << "\n";
        }

        std::cout << "\n========== 5. ИТЕРАТОР И ОПЕРАТОР '->' ==========\n";
        std::cout << "Обход склада через range-based for:\n";
        for (auto& item : whA) {
            std::cout << "  - Товар #" << item.getId() << ": " << item.getName() 
                      << " (Цена: " << item.getPrice() << "$)\n";
        }

        std::cout << "\nКонстантный обход (ConstWarehouseIterator):\n";
        const Warehouse& constRefA = whA;
        for (const auto& item : constRefA) {
            std::cout << "  [Const] " << item.getName() << " | Вес: " << item.getWeight() << " кг\n";
        }

        std::cout << "\n========== 6. ИСТИННЫЙ ПЕРЕНОС ТОВАРА (TRANSFERTO) ==========\n";
        Product* macbook = whA.findById(2);
        if (macbook) {
            std::cout << "Вызов macbook->transferTo(whB)...\n";
            macbook->transferTo(whB); // Перенос вызывается у самого товара
        }

        whA.printAll();
        whB.printAll();

        std::cout << "\n========== 7. ГЛУБОКОЕ КОПИРОВАНИЕ (RULE OF FIVE) ==========\n";
        Warehouse whACopy = whA;
        std::cout << "Создана копия whA. Проверяем идентичность ID товаров:\n";
        whACopy.printAll();

        std::cout << "\n========== 8. ПЕРЕМЕЩЕНИЕ СКЛАДА (MOVE SEMANTICS) ==========\n";
        Warehouse whMoved = std::move(whACopy);
        std::cout << "Склад перемещен. Проверяем обновление владельца у товаров:\n";
        whMoved.printAll();

        std::cout << "\n========== 9. УДАЛЕНИЕ ПО ID ==========\n";
        std::cout << "Удаляем товар с ID 1...\n";
        whA.removeById(1);
        whA.printAll();

        std::cout << "\nВСЕ ТЕСТЫ И СЦЕНАРИИ УСПЕШНО ЗАВЕРШЕНЫ!\n";

    } catch (const std::exception& ex) {
        std::cerr << "Критическая ошибка: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}