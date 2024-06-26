/*  Exercise 3.43: Write three different versions of a program to print the elements of ia.One version should use a range 
    for to manage the iteration, the other two should use an ordinary for loop in one case using subscripts and in the other
    using pointers. In all three programs write all the types directly. That is, do not use a type alias, auto, or decltype
     to simplify the code. */

#include <iostream>
#include <iterator>

int main(){
    constexpr size_t row_sz = 3, col_sz = 4;
    int ia[row_sz][col_sz] =  {{1,2,4,8},
                                {16,32,64,128},
                                {256,512,1024,2048}};

    //  using 'range for' to print the array
    std::cout << std::endl;
    for( int (&row)[col_sz] : ia ){     //  row is declared as reference, otherwise row will ptr to array of four int. if-
        for( int ele : row ){           //  -that's the case then 2nd for will be illegal, as we are trying to assign ptr to int
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //  using subscript to print the array
    for( size_t i = 0; i < row_sz; ++i){
        for( size_t j = 0; j < col_sz; ++j ){
            std::cout << ia[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //  using pointers to print the array
    for( int (*p)[4] = ia; p != ia + row_sz; ++p){       //  (or)    p != std::end(ia) 
        for( int *q = *p; q != *p + col_sz; ++q){
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
