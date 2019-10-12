// Example program
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h> /* time */

int main()
{
    srand(time(NULL));
    int num1 = rand() % 4 + 1;
    int num2 = rand() % 4 + 1;
    int num3 = rand() % 3 + 1;
    int num4 = rand() % 3 + 1;

    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    std::cout << num3 << std::endl;
    std::cout << num4 << std::endl;

    int caseNumber = stoi(std::to_string(num1) + std::to_string(num3));
    int caseNumber2 = stoi(std::to_string(num2) + std::to_string(num4));
    std::cout << caseNumber << std::endl;
    switch (caseNumber)
    {
    case 11:
        std::cout << "Case 11 ";
        break;
    case 12:
        std::cout << "Case 11 ";
        break;
    case 13:
        std::cout << "Case 11 ";
        break;
    case 21:
        std::cout << "Case 11 ";
        break;
    case 22:
        std::cout << "Case 11 ";
        break;
    case 23:
        std::cout << "Case 11 ";
        break;
    case 31:
        std::cout << "Case 11 ";
        break;
    case 32:
        std::cout << "Case 11 ";
        break;
    case 33:
        std::cout << "Case 11 ";
        break;
    case 41:
        std::cout << "Case 11 ";
        break;

    case 42:
        std::cout << "Case 11 ";
        break;

    case 43:
        std::cout << "Case 11 ";
        break;

    default:
        break;
    }
}
