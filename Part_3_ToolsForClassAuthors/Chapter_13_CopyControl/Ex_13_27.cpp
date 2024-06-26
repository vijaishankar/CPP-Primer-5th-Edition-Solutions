/************************************************************************************************************************************************************
 * @file Ex_13_27.cpp
 * @brief Exercise 13.27: Define your own reference-counted version of HasPtr.
 * @date 2024-01-24
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

//  class is defined to have pointer like behaviour, that is objects copied and assigned share state
#include <iostream>
#include <memory>
class HasPtr {
public:
    HasPtr(const std::string& s = std::string())
        : ps(new std::string(s)), i(0), use(new size_t(1)) {}
    HasPtr(const HasPtr& hp) : ps(hp.ps), i(hp.i), use(hp.use) {
        ++*use;
        std::cout << "copy constructor called" << std::endl;
    } 

    HasPtr & operator=(const HasPtr &source){
        ++*source.use;
        if(--*use == 0){
            delete ps;
            delete use;
            std::cout << "destructor is run and the memory allocated to hold the string is deleted" << std::endl;
        }
        ps = source.ps;
        use = source.use;

        return *this;
    }
    ~HasPtr(){
        if(--*use == 0){
            delete ps;
            delete use;
            std::cout << "destructor is run and the memory allocated to hold the string is deleted" << std::endl;
        } 
        
    }

    void info(){
        if(*use){
            std::cout << ps << " " << *ps << " " << *use << std::endl;
        }else{
            std::cout << "no object present" << std::endl;
        }
    }
private :
    std::string* ps;
    int i;
    size_t *use;
};

int main(){
    std::cout << "HasPtr p1(\"hello\"), p2(\"world\")" << std::endl;
    HasPtr p1("hello"), p2("world");
    p1.info();
    p2.info();
    std::cout << "HasPtr p3(p1)" << std::endl;
    HasPtr p3(p1);
    p1.info();
    p2.info();
    p3.info();
    std::cout << "p1 = p2" << std::endl;
    p1 = p2;
    p1.info();
    p2.info();
    p3.info();
    p3 = p1;
    p1.info();
    p2.info();
    p3.info();
    return 0;

}