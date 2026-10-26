#include "logging.h"

void LoggingProxy::logWarehouseAdd(Warehouse& wh, std::unique_ptr<Product> product) {
    std::cout << "[LOG][WAREHOUSE] Adding: " << product->getName() << std::endl;
    wh.addProduct(std::move(product));
}

void LoggingProxy::logWarehouseRemoveById(Warehouse& wh, int id) {
    std::cout << "[LOG][WAREHOUSE] Removing id=" << id << std::endl;
    wh.removeById(id);
}

std::unique_ptr<Product> LoggingProxy::logFactoryCreate(ProductFactory& factory,
                                                         const std::string& name,
                                                         int price, int quantity, double weight) {
    std::cout << "[LOG][FACTORY] Creating: " << name << std::endl;
    return factory.createProduct(0, name, price, quantity, weight);
}

void LoggingProxy::logChangeQuantity(Product& p, int delta) {
    std::cout << "[LOG][PRODUCT] " << p.getName() << " qty+" << delta << std::endl;
    p.changeQuantity(delta);
}

void LoggingProxy::logSetPrice(Product& p, const Price& newPrice) {
    std::cout << "[LOG][PRODUCT] " << p.getName() << " price=" << newPrice.getValue() << std::endl;
    p.setPrice(newPrice);
}