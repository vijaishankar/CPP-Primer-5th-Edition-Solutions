/************************************************************************************************************************************************************
 * @file Ex_1_15.cpp
 * @brief Exercise 1.15: Write programs that contain the common errors discussed in the box on page 16. Familiarize 
 * yourself with the messages the compiler generates.
 * @date 2024-03-14
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>

int main() {
    // syntax errors
    std::cout << "colon at the end of statement instead of semicolon, error : missing semicolon" << std::endl:
    std::cout << string_literal should be marked with double quotes, error : unknown identifier string_literal << std::endl;
    std::cout << "out put operator is required to write something." std::endl;
 
    // declaration errors
    int v1;
    std::cout << "uses v instead of v1, error : v is not declared " << v << std::endl;
    cout << "std::cout should be used, as cout is unkown" << std::endl;

    // type error
    int i = "string literal cannot be assigned to in, error : no known conversion from const char * to int";

    return 0  // missing semicolon
}