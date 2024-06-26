/************************************************************************************************************************************************************
 * @file Ex_16_51.cpp
 * @brief Exercise 16.51: Determine what sizeof...(Args) and sizeof...(rest) return for each call to foo in this 
 * section.
 * @date 2024-02-16
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#include<iostream>

template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest) {
    std::cout << t << " " << sizeof...(Args) << " " << sizeof...(rest) << std::endl;
}

int main() {

    int i = 0; double d = 3.14; std::string s = "how now brown cow";
    foo(i, s, 42, d); //  sizeof...(Args) = 3   sizeof...(rest) = 3
    foo(s, 42, "hi"); //  sizeof...(Args) = 2   sizeof...(rest) = 2 
    foo(d, s); //   sizeof...(Args) = 1   sizeof...(rest) = 1
    foo("hi");  //  sizeof...(Args) = 0   sizeof...(rest) = 0;

    return 0;
}

/************************************************************************************************************************************************************
 * sizeof...(template_parameter_pack) and size...of(function_parameter_pack) will always remains the same. It's a misunderstanding
 * that template parameter pack will consists of different types, whether the types are same or different it allways 
 * contains all the types in the arguments of the call.
 * so in first case
 *  T is deduced as int(1st argument), 
 *  s, 42, d,  types[std::string, int, double] of the remaining arguments forms the template parameter pack
 *  function parameter pack will contain  s, 42, d
 * 
 *************************************************************************************************************************************************************/

