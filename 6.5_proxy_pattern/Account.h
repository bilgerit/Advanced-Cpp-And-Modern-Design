// Tobias Bilgeri, 8.2.2024
#pragma once
class Account {
public:
    virtual ~Account() {}
    virtual void Withdraw(double amount) = 0;
    virtual double GetBalance() const = 0;
};
