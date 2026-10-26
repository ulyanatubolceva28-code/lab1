#include <iostream>
#include "warehouse.h"
#include "products.h"
#include "factory.h"
#include "logging.h"

void scenario1() {
    std::cout << "\n=== СЦЕНАРИЙ 1: Создание склада, фабрики, итератор ===\n";
    Warehouse wh(10);

    SmartphoneFactory sf; LaptopFactory lf; TShirtFactory tsf;
    JacketFactory jf; MilkFactory mf; BreadFactory bf;

    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(sf, "iPhone 15", 999, 50, 0.2));
    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(lf, "MacBook Pro", 2499, 20, 1.6));
    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(tsf, "Cotton T-Shirt", 29, 100, 0.2));
    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(jf, "Leather Jacket", 199, 30, 1.2));
    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(mf, "Whole Milk", 3, 200, 1.0));
    LoggingProxy::logWarehouseAdd(wh, LoggingProxy::logFactoryCreate(bf, "Sourdough Bread", 5, 150, 0.5));

    std::cout << "\n--- Все товары через итератор: ---" << std::endl;
    for (auto& p : wh) std::cout << p.toString() << std::endl;
}

void scenario2() {
    std::cout << "\n=== СЦЕНАРИЙ 2: Копирование склада ===\n";
    Warehouse wh1(10);
    SmartphoneFactory sf;
    wh1.addProduct(sf.createProduct(0, "Samsung Galaxy", 799, 40, 0.19));
    wh1.addProduct(sf.createProduct(0, "Google Pixel", 699, 30, 0.18));

    Warehouse wh2(wh1);

    std::cout << "\n--- Оригинал до изменения: ---" << std::endl;
    wh1.printAll();

    for (auto& p : wh2) LoggingProxy::logChangeQuantity(p, -10);

    std::cout << "\n--- Копия после изменения: ---" << std::endl;
    wh2.printAll();

    std::cout << "\n--- Оригинал (не изменён): ---" << std::endl;
    wh1.printAll();
}

void scenario3() {
    std::cout << "\n=== СЦЕНАРИЙ 3: Перемещение склада ===\n";
    Warehouse wh1(10);
    LaptopFactory lf;
    wh1.addProduct(lf.createProduct(0, "Dell XPS", 1299, 15, 1.8));
    wh1.addProduct(lf.createProduct(0, "HP Spectre", 1199, 10, 1.5));

    std::cout << "\n--- wh1 до перемещения: ---" << std::endl;
    wh1.printAll();

    Warehouse wh2(std::move(wh1));

    std::cout << "\n--- wh2 после перемещения: ---" << std::endl;
    wh2.printAll();
    std::cout << "wh1 size after move: " << wh1.getSize() << std::endl;
}

void scenario4() {
    std::cout << "\n=== СЦЕНАРИЙ 4: Поиск и удаление ===\n";
    Warehouse wh(10);
    SmartphoneFactory sf; TShirtFactory tsf; MilkFactory mf;

    auto p1 = sf.createProduct(0, "iPhone", 999, 50, 0.2);
    auto p2 = sf.createProduct(0, "Samsung", 799, 40, 0.19);
    auto p3 = tsf.createProduct(0, "T-Shirt", 29, 100, 0.2);
    auto p4 = mf.createProduct(0, "Milk", 3, 200, 1.0);

    int id1 = p1->getId();
    int id2 = p2->getId();

    wh.addProduct(std::move(p1));
    wh.addProduct(std::move(p2));
    wh.addProduct(std::move(p3));
    wh.addProduct(std::move(p4));

    // Поиск по ID
    Product* found = wh.findById(id1);
    if (found) std::cout << "\nНайден по ID=" << id1 << ": " << found->toString() << std::endl;

    // Поиск по категории
    auto electronics = wh.findByCategory("electronics");
    std::cout << "\nЭлектроника (" << electronics.size() << "):" << std::endl;
    for (auto* p : electronics) std::cout << "  " << p->toString() << std::endl;

    // Удаление по ID
    LoggingProxy::logWarehouseRemoveById(wh, id2);
    std::cout << "\nПосле удаления ID=" << id2 << ":" << std::endl;
    wh.printAll();

    // Удаление по индексу
    wh.removeByIndex(0);
    std::cout << "\nПосле удаления по индексу 0:" << std::endl;
    wh.printAll();
}

void scenario5() {
    std::cout << "\n=== СЦЕНАРИЙ 5: transferTo, изменение цены/остатка ===\n";
    Warehouse wh1(10), wh2(10);
    SmartphoneFactory sf;
    wh1.addProduct(sf.createProduct(0, "iPhone 15 Pro", 1199, 50, 0.22));

    std::cout << "\n--- wh1 до transferTo: ---" << std::endl;
    wh1.printAll();

    Product* p = wh1.findById(wh1.begin() != wh1.end() ? (*wh1.begin()).getId() : -1);
    if (p) p->transferTo(wh2);

    std::cout << "\n--- wh2 после transferTo: ---" << std::endl;
    wh2.printAll();

    // Изменяем первый товар в wh2
    for (auto& prod : wh2) {
        LoggingProxy::logChangeQuantity(prod, -5);
        LoggingProxy::logSetPrice(prod, Price(1099));
        break; // только первый
    }

    std::cout << "\n--- wh2 после изменений: ---" << std::endl;
    wh2.printAll();
}

int main() {
    try {
        scenario1(); scenario2(); scenario3(); scenario4(); scenario5();
        std::cout << "\nВсе сценарии выполнены успешно!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}