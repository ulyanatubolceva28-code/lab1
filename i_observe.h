#pragma once

#include "order_event.h"

namespace lab2 {

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onOrderEvent(const OrderEvent& event) = 0;
};

}