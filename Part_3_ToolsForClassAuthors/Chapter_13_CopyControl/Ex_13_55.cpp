/************************************************************************************************************************************************************
 * @file Ex_13_55.cpp
 * @brief Exercise 13.56: What would happen if we defined sorted as: 
 * Foo Foo::sorted() const & { 
 *      Foo ret(*this); 
 *      return ret.sorted(); 
 * }
 * @date 2024-01-28
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * ret(*this) , copy_constructs the Foo object ret.
 * ret.sorted(), as ret is lvalue, it is a recursive call.
 * again a ret object will be constructed
 * again ret.sorted will make a recursice call resulting in a recursive loop
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>

class Foo{
    public :
        Foo(const std::initializer_list<int> &il) : data(il.begin(), il.end()) { std::cout << "Foo(std::initializer_list<int> &il) : " << std::endl;}
        Foo(const Foo &f) : data(f.data){ std::cout << "Foo(const Foo &f) : " << std::endl;}
        Foo(Foo &&f) : data(std::move(f.data)) { std::cout << "Foo(Foo &&f) : " << std::endl;}
        Foo sorted() const &{
            std::cout << "Foo sorted() const : " << std::endl;
            Foo ret(*this);
            return ret.sorted();    // causes recursive loop
        }       
    private :
        std::vector<int> data;
};

int main(){
    Foo f1{56,45,89,10};
    Foo f = f1.sorted();
}

