/************************************************************************************************************************************************************
 * @file Ex_10_25.cpp
 * @brief Exercise 10.25: In the exercises for § 10.3.2 (p. 392) you wrote a version of biggies that uses partition. Rewrite
 *        that function to use check_size and bind
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

void biggies(std::vector<std::string> &words);
void elimDups(std::vector<std::string> &words);
bool checksz(const std::string &str, std::string::size_type sz);

using std::placeholders::_1;
std::string::size_type sz = 6;
auto checkWithchecksz = std::bind(checksz, _1,sz);

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

    // code to count the number of words greater than 6
    auto count = std::count_if(words.begin(), words.end(), checkWithchecksz);
    std::cout << "\nthere are " << count << " words lesser than or equal to " << sz << " letters" << std::endl;

    //  code to partition the list wiht element whose size is greater than sz preceding the rest with original order preserved
    auto endOfMatches = std::stable_partition(words.begin(), words.end(), checkWithchecksz);
    std::cout << "\nwords lesser than or equal to  " << sz << " letter" << std::endl;
    std::for_each(words.begin(), endOfMatches, [](std::string &str){ std::cout << str << " " ;});
    
    return;
}

void elimDups(std::vector<std::string> &words){

    // code to sort the list
    std::sort(words.begin(), words.end());
    std::cout << "\nsorted list of words with duplicates : " << std::endl;
    std::for_each(words.begin(), words.end(), [](const std::string &str){std::cout << str << " ";});
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

bool checksz(const std::string &str, std::string::size_type sz){
    return str.size() <= sz;
}