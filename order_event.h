#pragma once

#include "order_status.h"

#include <chrono>

namespace lab2 {

struct OrderEvent {
    int orderId;
    OrderStatus oldStatus;
    OrderStatus newStatus;
    std::chrono::system_clock::time_point occurredAt;
};

}