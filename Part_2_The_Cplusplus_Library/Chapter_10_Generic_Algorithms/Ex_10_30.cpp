/************************************************************************************************************************************************************
 * @file Ex_10_30.cpp
 * @brief Exercise 10.30: Use stream iterators, sort, and copy to read a sequence of integers from the standard input, sort
 *        them, and then write them back to the standard output.
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(){
    std::cout << "Enter the list of nums : " << std::endl;
    std::istream_iterator<int> i_istrm_iter(std::cin), end;     // initialises an istream_iterator to read int from cin
    std::vector<int> ivec(i_istrm_iter, end);       //  initialises a vector of int from cin using istream_iterator and end_iter

    std::sort(ivec.begin(), ivec.end());    // sorts the vector
    std::ostream_iterator<int> i_ostrm_iter(std::cout , " ");   // initialises an ostream_iterator to write int followed by space to cout 
    std::copy(ivec.begin(), ivec.end(), i_ostrm_iter);      // copies all items in the vector to cout using ostream_iterator.

    return 0;
}
