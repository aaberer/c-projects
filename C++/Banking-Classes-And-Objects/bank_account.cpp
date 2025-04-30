//
// Created by Andrew Aberer on 2/12/25.
//

#include "bank_account.h"

BankAccount::BankAccount() : running_balance(0.0) {}

double BankAccount::balance() const {return running_balance;}

void BankAccount::deposit(double amount) {
    if (amount >= 0) {running_balance += amount;}
}

void BankAccount::withdraw(double amount) {
    if (amount >= 0 && amount <= running_balance) {running_balance -= amount;}
}