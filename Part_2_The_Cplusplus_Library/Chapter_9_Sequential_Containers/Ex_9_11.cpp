/************************************************************************************************************************************************************
 * @file Ex_9_11.cpp
 * @brief Exercise 9.11: Show an example of each of the six ways to create and initialize a vector. Explain what values each
 *        vector contains.
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>

int main(){
    std::vector<int> ivec1;              //  default initialisation, an empty vector.
    std::vector<int> ivec2(ivec1);       //  copy initialisation, ivec2 is initialised with the copy of ivec1( container type and element type should match).
    std::vector<int> ivec3(ivec1);       //  copy initialisation, ivec2 is initialised with the copy of ivec1( container type and element type should mathc).
    std::vector<int> ivec4{a,b,. . .};   //  list initialisation, copy of each element in the initialiser list, the type should 
                                         //  be same or compatible with the type of element in the vector.
    std::vector<int> ivec4 = {a,b,. . .};//  list initialisation, copy of each element in the initialiser list, the type should 
                                         //  be same or compatible with the type of element in the vector.
    std::vector<int> ivec5(b,e);         //  b and e refers to the begin and one past the last element in the range
                                         //  vetor will be initialised with each element in the range up to but not including 
                                         //  the one e refers.
    std::vector<int> ivec6(10);          //  constructor that takes size, ivec6 is vector of 10 ints, value initialised to 0 .
    std::vector<int> ivec7(10,1234);     //  constructor that takes size and a initial value, ivec7 is a vector of 10 int types 
                                         //  initialised with value 1234.                               
      
}