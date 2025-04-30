//
// Created by Andrew Aberer on 2/12/25.
//

#include <iostream>
#include <string>

int main()
{
    while (true)
    {
        std::string token;
        std::cin >> token;

        if (token == "exit"){break;}

        double a = std::stod(token);

        char op;
        double b;
        std::cin >> op >> b;

        double result = 0;

        switch(op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if(b == 0){continue;}
            result = a / b;
            break;
        default:
            continue;
        }

        std::cout << result << "\n";
    }
    return 0;
}

