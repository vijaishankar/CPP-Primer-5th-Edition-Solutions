/************************************************************************************************************************************************************
 * @file Ex_10_33.cpp
 * @brief Exercise 10.33: Write a program that takes the names of an input file and two output files. The input file should
 *        hold integers. Using an istream_iterator read the input file. Using ostream_iterators, write the odd numbers into
 *        the first output file. Each value should be followed by a space. Write the even numbers into the second file. Each
 *        of these values should be placed on a separate line.
 * @date 2024-01-07
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <iterator>
#include <fstream>

int main(int argc, char **argv){
    
    std::ifstream ifile(*(argv + 1));
    if(!ifile){
        std::cerr << "Unable to open "<< argv + 1 << std::endl;
        return -1;
    }

    std::ofstream oddFile(*(argv + 2)), evenFile(*(argv + 3));
    if(!oddFile){
        std::cerr << "unable to open " << argv + 2 << std::endl;
        return -1;
    }
    if (!evenFile) {
        std::cerr << "unable to open " << *argv + 3 << std::endl;
        return -1;
    }

    std::istream_iterator<int> int_iter(ifile), end;
    std::ostream_iterator<int> odd_iter(oddFile," "), even_iter(evenFile,"\n");

    int val;
    while (int_iter != end){
        val = *int_iter++;
        if (val % 2) {
            *odd_iter++ = val;
        } else {
            *even_iter++ = val;
        }
    }

    std::cout << "files writen" << std::endl;
    return 0;
}
