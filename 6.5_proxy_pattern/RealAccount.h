// Tobias Bilgeri, 8.2.2024
#pragma once
#include "Account.h"
class RealAccount : public Account {
private:
    double _balance;

public:
    RealAccount(double initialBalance) : _balance(initialBalance) {}

    void Withdraw(double amount) override {
        if (_balance < amount) {
            throw NoFundsException();
        }
        _balance -= amount;
    }

    double GetBalance() const override {
        return _balance;
    }
};