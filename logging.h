#pragma once
#include <iostream>
#include <string>
#include "warehouse.h"
#include "factory.h"

class LoggingProxy {
public:
    static void logWarehouseAdd(Warehouse& wh, std::unique_ptr<Product> product);
    static void logWarehouseRemoveById(Warehouse& wh, int id);
    static std::unique_ptr<Product> logFactoryCreate(ProductFactory& factory,
                                                      const std::string& name,
                                                      int price, int quantity, double weight);
    static void logChangeQuantity(Product& p, int delta);
    static void logSetPrice(Product& p, const Price& newPrice);
};