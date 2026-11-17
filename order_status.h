#pragma once

#include <string>

namespace lab2 {

enum class OrderStatus {
    Pending,
    Paid,
    Shipped,
    Delivered,
    Cancelled
};

std::string toString(OrderStatus status);

}