// Proxy for RealAccount
// Tobias Bilgeri, 8.2.2024
#pragma once
#include "RealAccount.h"
class ProtectedAccount : public Account {
private:
    RealAccount _account;
    std::string _password;

public:
    ProtectedAccount(double initialBalance, const std::string& password)
        : _account(initialBalance), _password(password) {}

    void Withdraw(double amount) override {
        _account.Withdraw(amount);
    }

    double GetBalance() const override {
        throw NoAccessException();
    }

    double GetBalance(const std::string& providedPassword) const {
        if (providedPassword != _password) {
            throw NoAccessException();
        }
        return _account.GetBalance();
    }
};