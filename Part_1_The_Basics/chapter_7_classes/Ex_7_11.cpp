/*  Exercise 7.11: Add constructors to your Sales_data class and write a program to use each of the constructors. */

#include <iostream>

struct Sales_data{
    std::string isbn() const {          //   declared as const member function so that we can call isbn() for const objects
        return book_no;
    }
    
    Sales_data & combine(const Sales_data &rhs);
    Sales_data() = default;                        //   default constructor
    Sales_data(std::istream &is);                  //   constructor that takes one parameter of type istream reference
    //  constructor that takes only isbn no
    Sales_data(const std::string book_no_p) : book_no(book_no_p) {}
    //  constructor that takes isbn no, units sold, and revenue
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {}
    
    std::string book_no;                           //   isbn no                     
    unsigned units_sold = 0;                           //   total no of units sold
    double revenue = 0;                                //   revenue from the total sale of this book
};

Sales_data & Sales_data::combine(const Sales_data &rhs){  //   returns reference of the object for which combine was called, it-
    units_sold += rhs.units_sold;                         //   -mimics the += operator's return value   
    revenue += rhs.revenue;

    return *this;                                   //  this is pointer which is rvalue, to get lvalue we dereference it
}

std::istream & read(std::istream &is, Sales_data &item){
    std::cout << "Enter the transactin details[isbn count price] : \n";
    double price;
    is >> item.book_no >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream & print(std::ostream &os, const Sales_data &item){
    os << item.book_no << " " << item.units_sold << " " << item.revenue ;
    return os;
}

Sales_data::Sales_data(std::istream &is){
    read(is, *this);
}

int main(){
    Sales_data b1, b2(std::cin), b3("c++_primer"), b4("discrete math", 20, 2.5);
    print(print(print(print(std::cout,b1),b2),b3),b4);
    
    return 0;
}
