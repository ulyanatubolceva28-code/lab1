#pragma once

#include "i_observer.h"

#include <vector>

namespace lab2 {

class IObservable {
public:
    IObservable() = default;
    IObservable(const IObservable&) noexcept;
    IObservable& operator=(const IObservable& other) noexcept;
    virtual ~IObservable() = default;

    void attachObserver(IObserver* observer);
    void detachObserver(IObserver* observer);

protected:
    void notifyObservers(const OrderEvent& event);

private:
    std::vector<IObserver*> observers_;
};

}