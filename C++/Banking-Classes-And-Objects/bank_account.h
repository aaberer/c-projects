//
// Created by Andrew Aberer on 2/12/25.
//

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H


class BankAccount {
private:
    double running_balance;
public:
    BankAccount();
    double balance() const;
    void deposit(double amount);
    void withdraw(double amount);
};

#endif //BANK_ACCOUNT_H
