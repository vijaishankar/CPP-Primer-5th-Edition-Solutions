/************************************************************************************************************************************************************
 * @file Ex_9_44.cpp
 * @brief Exercise 9.44: Rewrite the previous function using an index and replace.
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

std::string & replaceStr(std::string &s, const std::string oldVal, const std::string newVal){
    for(std::string::size_type i = 0; i != s.size(); ){         //  iterates through s using subscript
        if( i + oldVal.size() <= s.size()){     // checks remaining characters minimum the length of oldVal
            std::string seq(s, i, oldVal.size());           //  constructs a seq of characters from position i to the length of oldVal from string s
            if( seq == oldVal){     
                s.replace(i, oldVal.size(), newVal);
                i += oldVal.size();
            }else{
                ++i;
            }
        }else{
            return s;
        }
    }
}

int main(){
    std::string s1("onetwothou thou");
    std::string s2("thruonetwothree thrufour fivethrued");
    std::cout << replaceStr(s1,"thou","though") << std::endl;
    std::cout << replaceStr(s2, "thru", "thrugh") << std::endl;

    return 0;
}