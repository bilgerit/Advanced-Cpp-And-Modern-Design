// Subject class
//
// Observers are implement as std::function objects rather than some custom base /
// derived class type.
// Additionally, I also incorporate boost-signals2 here in the same class
// for brevity.
//
// Tobias Bilgeri, 15.02.2024
#pragma once
#include <functional>
#include <boost/signals2.hpp>
#include <iostream>

template<template<typename> class Container>
class Subject {
    // Subject / Observable
    // Connects to boost::signals2-type slots + std::function<void(int)> type observers.
public:
    // std::function based observer template:
    using observer_t = std::function<void(int)>;

    // templated observer container:
    using observers_t = Container<observer_t*>;

    // boost::signals2 based observers/slots:
    using signal_t = boost::signals2::signal<void(int)>;

    Subject() = default;

    void attach(observer_t* observer) {
        // add observer
        observers_.push_back(observer);
    }

    void detach(observer_t* observer) {
        // remove observer
        observers_.erase(
            std::remove(
                observers_.begin(), 
                observers_.end(), 
                observer
            ), 
            observers_.end()
        );
    }

    void notify_observers() {
        // notify / trigger observers
        // using state of subject (=value_ variable)
        std::cout << "\n" << typeid(this).name() << ": notifying observers: \n";
        for (observer_t* obs : observers_) {
            (*obs)(value_);
        }
    }

    void notify_slots() {
        // notify / trigger slots connected to signal
    	// using state of subject (=value_ variable)
        std::cout << "\n" << typeid(this).name() << ": notifying slots: \n";
        signal_(value_);
    }

    void increaseCounter() {
        // change subject state by increasing value_
        // then, notify observers and slots
        ++value_;
        notify_observers();
        notify_slots();
    }

    void decreaseCounter() {
        // change subject state by decreasing value_
        // then, notify observers and slots
        --value_;
        notify_observers();
        notify_slots();
    }

    signal_t& signal() {
        // obtain mutable reference to signal member
        // use this to directly allow users to interface with the signal_
        // member, and use its members (such as .connect(signal_t) or similar) 
        return signal_;
    }

private:
    int value_ = 0;
    observers_t observers_;
    signal_t signal_;
};