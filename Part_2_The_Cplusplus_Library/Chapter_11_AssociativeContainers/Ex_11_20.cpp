/************************************************************************************************************************************************************
 * @file Ex_11_20.cpp
 * @brief Exercise 11.20: Rewrite the word-counting program from § 11.1 (p. 421) to use insert instead of subscripting. Which
 *        program do you think is easier to write and read? Explain your reasoning
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <map>
#include <utility>

int main(){
    std::map<std::string, size_t> wordCount;    
    std::string word;
    while(std::cin >> word){
        std::pair<std::map<std::string, size_t>::iterator, bool> p =  wordCount.insert({word, 1});
        if(!p.second){
            ++p.first->second;
        }
    }

    for( auto ele : wordCount){
        std::cout << ele.first << " occurs " << ele.second << " times" << std::endl;
    }

    return 0;
}

/************************************************************************************************************************************************************
 * using subscript and the key is much easier to read and write as the following expression
 *  ++wordCount[word] does two things in single expression
 *      1. inserts key in the map if key already present nothing happens or else key is added
 *      2. whether added or already present value associated to the key is returned, then ++ increments the value of the key
 * It is less verbose than compared to using iterator
 *************************************************************************************************************************************************************/
