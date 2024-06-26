/************************************************************************************************************************************************************
 * @file Ex_16_46.cpp
 * @brief Exercise 16.46: Explain this loop from StrVec::reallocate in § 13.5 (p. 530):
 * for (size_t i = 0; i != size(); ++i)
 *      alloc.construct(dest++, std::move(*elem++));
 * @date 2024-02-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * for (size_t i = 0; i != size(); ++i)
 *      alloc.construct(dest++, std::move(*elem++));
 * 
 *  alloc.construct() constructs a new element at memory pointed by dest, from the rvalue reference to the elem returned
 *  by std::move(), resulting alloc.construct() using move constructor of the element type, which moves the value in elem to dest.
 *  
 *  in this call, std::move() takes an lvalue reference and returns an rvalue reference to the elem type. It does so 
 *  by using static_cast the lvalue reference to rvalue_reference.
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <type_traits>

template <typename T>
typename std::remove_reference<T>::type && move(T &&val) {
    return static_cast<typename std::remove_reference<T>::type &&>(val);
}

int main() {
    int n = 78;
    int &&rr = move(n);
    std::cout << rr << std::endl;
    /************************************************************************************************************************************************************
     * If we call move with lvalue, since function parameter is rvalue rference to template parameter,
     *        T is deduced as int &, lvalue reference
     *     return type :  int &&
     *        remove_reference<int &>::type  will return int as type by removing the references
     *        typename is used to tell the compiler it is a type returned by remove_reference<T>::type
     *        return type also has additional &&, to say return type is rvalue reference to type returned by remove_reference<T>::type
     *        auto can also be used to get the return type as rvalue reference from the result of the return statement.
     *     return statement :  rvalue reference to val
     *        since T is int &, by referencing collapsing, val is int &.
     *        to return a rvalue reference, to bind val to rvalue reference, val is static_cast from lvaue reference to rvalue reference
     *        remove_reference<T>::type to get int which is then combined with && as argument to static_cast to cast an rvalue reference
     * 
     * If we call move with rvalue, T is refered to type
     *        T is deduced as int
     *     return type : int &&
     *        remove_reference<int>::type does nothing, just returns T, which then along with && tells the return type is rvalue reference
     *     return statement :  rvalue reference to val
     *        since T is int, val is rvalue reference
     *        remove_refernce<int>::type, returns int
     *        static_cast<int &&>(val), does nothing as val is already rvalue reference.
     *      
     *************************************************************************************************************************************************************/
}