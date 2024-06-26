/*  Exercise 2.34: Write a program containing the variables and assignments from the previous exercise. Print the variables
 *  before and after the assignments to check whether your predictions in the previous exercise were correct. If not, study
 *  the examples until you can convince yourself you know what led you to the wrong conclusion. */

#include <iostream>

int main(){

    int i = 0, &r = i;             
    auto a = r;                
    const int ci = i, &cr = ci;                            
    auto b = ci;               
    auto c = cr;                                                                                                
    auto d = &i;                    
    auto e = &ci;                   
    const auto f = ci;              
    auto &g = ci;                   
    //auto &h = 42;                   
    const auto &j = 42;             
    auto k = ci, &l = i;            
    auto &m = ci, *p = &ci;         
    //auto &n = i, *p2 = &ci;         
    std::cout << a << " " ;
    a = 42;             //   ok
    std::cout << a << std::endl << b ;
    b = 42;             //   ok
    std::cout << " " << b << std::endl << c ;
    c = 42;             //   ok
    std::cout << " " << c << std::endl;
    //d = 42;             //   error : d is int *, so we have to dereference first
    //e = 42;             //   error : e is const int *, we should dereference e to get the object, and also e is pointer 
                          //   to const
    //g = 42;             //   error : g is const int &, we can't change the value through g
}    