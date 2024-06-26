/************************************************************************************************************************************************************
 * @file Ex_8_5.cpp
 * @brief Exercise 8.5: Rewrite the previous program to store each word in a separate element.
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(){
    std::ifstream ifile("notes.md");

    if(!ifile){                                 // checks if file open is unsuccessfull
        std::cerr << "Unable to open file ";
        return -1;
    }

    std::vector<std::string> wordvec;
    std::string word;
    // reads word by word and stores as a seperate element in the vector
    while(ifile >> word){      
        wordvec.push_back(word);
    }
    ifile.close();

    // prints the contents to the console
    for(auto iter = wordvec.cbegin(); iter != wordvec.cend(); ++iter){
        std::cout << *iter << " ";
    }

    

    return 0;
     
}