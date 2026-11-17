#include "order_status.h"

namespace lab2 {

std::string toString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending:
            return "pending";
        case OrderStatus::Paid:
            return "paid";
        case OrderStatus::Shipped:
            return "shipped";
        case OrderStatus::Delivered:
            return "delivered";
        case OrderStatus::Cancelled:
            return "cancelled";
    }

    return "unknown";
}

}