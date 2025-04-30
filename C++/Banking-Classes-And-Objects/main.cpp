//
// Created by Andrew Aberer on 2/12/25.
//

#include "bank_account.h"

#include <iostream>
#include <string>

int main() {
    BankAccount account;
    std::string command;
    double amount;

    while (true) {
        std::cin >> command;
        if (!std::cin)
            break;  // exit if input fails

        if (command == "exit") {break;}
        else if (command == "balance") {std::cout << account.balance() << "\n";}
        else if (command == "deposit") {
            std::cin >> amount;
            account.deposit(amount);
        } else if (command == "withdraw") {
            std::cin >> amount;
            account.withdraw(amount);
        }
    }
    return 0;
}
