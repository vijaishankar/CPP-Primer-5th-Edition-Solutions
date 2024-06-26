/************************************************************************************************************************************************************
 * @file Ex_1_20.cpp
 * @brief Exercise 1.20: http://www.informit.com/title/0321714113 contains a copy of Sales_item.h in the Chapter 1 code
 * directory. Copy that file to your working directory. Use it to write a program that reads a set of book sales 
 * transactions, writing each transaction to the standard output.
 * @date 2024-03-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include "Sales_item.h"   //  header file of Sales_item
#include <iostream> 
 
int main() {
    Sales_item item;
    std::cout << "Enter a set of book sales transactions :\n";

    while(std::cin >> item) {   //  repeat the block untill unable to read a Sales_item
        std::cout << item << "\n";
    }
    std::cout << std::endl;

    return 0;
}