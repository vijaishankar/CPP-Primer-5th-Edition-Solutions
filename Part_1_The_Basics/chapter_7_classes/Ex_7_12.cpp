/*  Exercise 7.12: Move the definition of the Sales_data constructor that takes an istream into the body of the Sales_data class.*/

#include <iostream>
#include <string>

/* forward declaration tells the compiler that defintion of the name will come afterwards, it is important when we use name- 
 * which is not defined yet, the form is 
 * class/struct class_name;
 * return_type function_name(param_list); */
 
struct Sales_data;   // forward declaration as read() declaration is using name Sales_data in its parameter list
std::istream & read(std::istream &, Sales_data &); // forward declaration Sales_data(std::istream &) constructor is usin read()

// definition of Sales_data class
struct Sales_data{
//  interface begins here
friend std::istream & read(std::istream &is, Sales_data &item);             //  by declaring read() as a friend, read() code will have access to non-public members of the class, friends are not affected by access specifier
friend std::ostream & print(std::ostream &os, const Sales_data &item);      //  every non-member function which is a part of the class interface to access non-public members need to declared as friend
public :
    std::string isbn() const {          //   declared as const member function so that we can call isbn() for const objects
        return book_no;
    }
    
    Sales_data & combine(const Sales_data &rhs);
    Sales_data() = default;                        //   default constructor
    Sales_data(std::istream &is){                  //   constructor that takes one parameter of type istream reference
        read(is, *this);
    }    
    //  constructor that takes only isbn no
    Sales_data(const std::string book_no_p) : book_no(book_no_p) {}
    //  constructor that takes isbn no, units sold, and revenue
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {}

//  interface ends here
//  implementation begins here
private :
    std::string book_no;                           //   isbn no                     
    unsigned units_sold = 0 ;                      //   total no of units sold
    double revenue = 0;                            //   revenue from the total sale of this book    
//  implemetation ends here                         
};

Sales_data & Sales_data::combine(const Sales_data &rhs){  //   returns reference of the object for which combine was called, it-
    units_sold += rhs.units_sold;                         //   -mimics the += operator's return value   
    revenue += rhs.revenue;

    return *this;                                   //  this is pointer which is rvalue, to get lvalue we dereference it
}

//  a funtion declaration doesn't make the function visible to the user code, a separate declaration is needed 
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

