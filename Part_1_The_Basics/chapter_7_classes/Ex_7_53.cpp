/************************************************************************************************************************************************************
 * @file Ex_7_54.cpp
 * @brief Exercise 7.53: Define your own version of Debug.
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * For a class to be a literal class
 * 1. Aggregate class with members only of literal types
 * 2. Non-Aggregate
 *      a) members should be only literal types
 *      b) Atleast one constexpr constructor which initialises all members
 *      c) in-class initialisers should be constexpr, if the member is of class type, then such class's constexpr constructor
 *         should be used
 *      d) The class must use default definition for its destructor  
 * It can have member functions of constexpr type
 *************************************************************************************************************************************************************/

#include <iostream>

// Following above rules the debug class is defined

class Debug{
public : 
    constexpr Debug(bool hw_p = true) : hw(hw_p), io(0), other(0) { }
    constexpr Debug(bool hw_p, bool io_p, bool other_p) 
        :   hw(hw_p), io(io_p), other(other_p) { }
    constexpr bool any() const {
        return hw || io || other;
    }
    constexpr bool get_hw() const {
        return hw;
    }
    constexpr bool get_io() const {
        return io;
    }
    bool get_other() const {         // though it is a const member function it is not a constexpr function   
        return other;
    }
    void set_hw(bool hw_p = true){
        hw = hw_p;
    }
    void set_io(bool io_p = true){
        io = io_p;
    }
    void set_other(bool other_p = true){
        other = other_p;
    }
private :
    bool hw;
    bool io;
    bool other;
};

int main(){
    constexpr Debug error1, error2(0,0,0);
    Debug error3(true,false,true);
    error3.set_other(false);
    std::cout << error3.get_other() << std::endl;
    constexpr bool val1 = error1.any();
    constexpr bool val2 = error2.any();
    std::cout << val1 << " " << val2 << error1.get_hw() << " " << error1.get_other() << std::endl;
    int arr1[error1.get_hw() + error2.get_hw()];
   // int arr2[error1.get_other()];  //error: ISO C++ forbids variable length array ‘arr2’ [-Wvla]
                                   //   int arr2[error1.get_other()];
   //                                          ^~~~       
    std::cout << sizeof(arr1) << std::endl;
}