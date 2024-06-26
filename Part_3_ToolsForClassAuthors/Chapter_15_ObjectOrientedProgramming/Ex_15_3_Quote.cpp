/************************************************************************************************************************************************************
 * @file Ex_15_3.cpp
 * @brief Exercise 15.3: Define your own versions of the Quote class and the print_total function.
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

// base class
class Quote {
public:     //  every one can access the members
    Quote() = default;

    Quote(const std::string& book_no_, double price_)
        : book_no(book_no_), price(price_)
    {}

    virtual double net_price(size_t count) const {   //  derived classes can override the definition 
        return price * count;
    }

    const std::string& isbn() const {   //   derived classes cannot override these non-virtual functions, they just inherit these
        return book_no;
    }

virtual ~Quote() = default; // base class destructor should be declared as virtual

private:   //  derived class don't have access to private members like users of the class     
    std::string book_no;    

protected:  //  derived class can access protected members but not the users
    double price;
};

void print_total(const Quote &item, size_t count){
    std::cout << "ISBN : " << item.isbn() << "\n" << 
              "net price : " << item.net_price(count) << std::endl;
}

