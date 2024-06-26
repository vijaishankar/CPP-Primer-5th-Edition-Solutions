/************************************************************************************************************************************************************
 * @file Ex_9_47.cpp
 * @brief Exercise 9.47: Write a program that finds each numeric character and then each alphabetic character in the string
 *        "ab2c3d7R4E6". Write two versions of the program. The first should use find_first_of,
 *         and the second find_first_not_of.
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

int main(){
    const std::string seq("ab2c3d7R4E6");

    //  version 1 using find_first_of begins here
    std::string::size_type pos = 0;
    std::string numbers{"0123456789"};
    std::cout << "The sequence[" << seq << "] has the following numbers : " << std::endl;
    while((pos = seq.find_first_of(numbers , pos)) != std::string::npos){
        std::cout << seq[pos] << " at " << pos << std::endl;
        ++pos;
    }

    std::string alphabets;
    for(auto ch = 'a'; ch <= 'z'; ++ch){
        alphabets.push_back(ch);
        alphabets.push_back(std::toupper(ch));
    }
    pos = 0;
    std::cout << "The sequence[" << seq << "] has the following alphabets : " << std::endl;
    while((pos = seq.find_first_of(alphabets, pos)) != std::string::npos){
        std::cout << seq[pos] << " at " << pos << std::endl;
        ++pos;
    }
    //  version 1 ends here

    // version 2 using find_last_of 
    pos = 0;
    std::cout << "The sequence[" << seq << "] has the following numbers : " << std::endl;
    while((pos = seq.find_first_not_of(alphabets, pos)) != std::string::npos){
        std::cout << seq[pos] << " at " << pos << std::endl;
        ++pos;
    }

    pos = 0;
    std::cout << "The sequence[" << seq << "] has the following alphabets : " << std::endl;
    while((pos = seq.find_first_not_of(numbers, pos)) != std::string::npos){
        std::cout << seq[pos] << " at " << pos << std::endl;
        ++pos;
    }

    return 0;
}
