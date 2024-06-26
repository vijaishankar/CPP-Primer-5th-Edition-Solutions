/************************************************************************************************************************************************************
 * @file Ex_10_16.cpp
 * @brief Exercise 10.16: Write your own version of the biggies function using lambdas.
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * @brief sorts the list relative to length by maintaining alphabatical order of the equal elements and then prints the words
 * bigger than given size
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void biggies(std::vector<std::string> &words);
void elimDups(std::vector<std::string> &words);

int main(){
    std::vector<std::string> wordlst;
    std::cout << "Enter the list of words : " << std::endl;
    std::string word;
    while(std::cin >> word){
        wordlst.push_back(word);
    }

    biggies(wordlst);
    return 0;
}

void biggies(std::vector<std::string> &words){
    
    // sorts the list in dict order, removes dup words and sorts by length by preserving dict order
    elimDups(words);

    //  code to find the first element whose size is greater or equal to sz
    std::string::size_type sz = 5;
    auto beg = std::find_if(words.begin(), words.end(), [sz](std::string &str){ return str.size() > sz ;});
    std::cout << "\nwords bigger than " << sz << " letter" << std::endl;
    std::for_each(beg, words.end(), [](std::string &str){ std::cout << str << " " ;});
    
    return;
}

void elimDups(std::vector<std::string> &words){

    // code to sort the list
    std::sort(words.begin(), words.end());
    std::cout << "\nsorted list of words with duplicates : " << std::endl;
    std::for_each(words.begin(), words.end(), [](std::string &str){ std::cout << str << " ";});
    std::cout << std::endl;

    // code to eliminate dups
    auto endUnique = std::unique(words.begin(), words.end());
    words.erase(endUnique, words.end());  //    erases the duplicate words
    std::cout << "\nSorted list of unique words : " << std::endl;
    std::for_each(words.begin(), words.end(), [](std::string &str){std::cout << str << " "; });
    std::cout << std::endl;

    // code to sort the list based on length preserving alphabetical order
    std::stable_sort(words.begin(), words.end(), [](const std::string &lhs,const std::string &rhs){ return lhs.size() < rhs.size(); });
    std::cout << "\nsorted list of words by length : " << std::endl; 
    std::for_each(words.begin(), words.end(), [](std::string &str){ std::cout << str << " ";});
    std::cout << std::endl;

    return;
}