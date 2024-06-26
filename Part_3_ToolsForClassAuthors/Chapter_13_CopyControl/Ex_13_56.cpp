/************************************************************************************************************************************************************
 * @file Ex_13_56.cpp
 * @brief Exercise 13.57: What if we defined sorted as:
 * Foo Foo::sorted() const & { 
 *  return Foo(*this).sorted(); 
 * }
 * @date 2024-01-28
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/


#include <iostream>
#include <vector>
#include <algorithm>

class Foo{
    friend std::ostream & print(std::ostream &, const Foo &f);
    public :
        Foo(const std::initializer_list<int> &il) : data(il.begin(), il.end()) { std::cout << "Foo(std::initializer_list<int> &il) : " << std::endl;}
        Foo(const Foo &f) : data(f.data){ std::cout << "Foo(const Foo &f) : " << std::endl;}
        Foo(Foo &&f) : data(std::move(f.data)) { std::cout << "Foo(Foo &&f) : " << std::endl;}
        Foo sorted() const &{
            std::cout << "Foo sorted() const : " << std::endl;
            return (*this).sorted();    // causes recursive loop, as dereferencing a pointer yields lvalue, so it makes a recursive call
        }      

        Foo sorted() && {
            std::cout << "Foo sorted() && : " << std::endl;
            std::sort(data.begin(), data.end());
        } 

    private :
        std::vector<int> data;
};

std::ostream & print(std::ostream &os, const Foo &f){
    os << "===========================" << std::endl;
    for( auto n : f.data){
        os << n << " ";
    }
    os << std::endl;
    return os;
}
int main(){
    Foo f1{56,45,89,10};
    Foo f = f1.sorted();
    print(std::cout , f);
}