#include "i_observable.h"

#include <algorithm>

namespace lab2 {

IObservable::IObservable(const IObservable&) noexcept {
}

IObservable& IObservable::operator=(const IObservable&) noexcept {
    return *this;
}

void IObservable::attachObserver(IObserver* observer) {
    if (observer == nullptr) {
        return;
    }

    if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
        observers_.push_back(observer);
    }
}

void IObservable::detachObserver(IObserver* observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void IObservable::notifyObservers(const OrderEvent& event) {
    const auto observersCopy = observers_;

    for (IObserver* observer : observersCopy) {
        if (
            observer != nullptr &&
            std::find(observers_.begin(), observers_.end(), observer) != observers_.end()
        ) {
            observer->onOrderEvent(event);
        }
    }
}

}