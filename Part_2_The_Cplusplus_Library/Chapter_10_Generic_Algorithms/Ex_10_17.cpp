/************************************************************************************************************************************************************
 * @file Ex_10_17.cpp
 * @brief Exercise 10.17: Rewrite exercise 10.12 from § 10.3.1 (p. 387) to use a lambda in the call to sort instead of the
 *        compareIsbn function.
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Sales_data;   
std::istream & read(std::istream &, Sales_data &); 


struct Sales_data{

friend std::istream & read(std::istream &is, Sales_data &item);     
friend std::ostream & print(std::ostream &os, const Sales_data &item);     
public :                            
    std::string isbn() const {      
        return book_no;
    }

    double avg_price() const;       
    Sales_data & combine(const Sales_data &rhs);

    
    Sales_data() : Sales_data("", 0, 0) {                    
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    Sales_data(std::istream & is) : Sales_data("",0,0) {   
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        read(is, *this);                                   
    }

    
    Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
        std::cout << "Sales_data(const std::string book_no_p) : invoked" << std::endl;
    }

    
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {
                std::cout << "Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked"
                          << std::endl;  
            }
    
private :                                          
    std::string book_no;                           
    unsigned units_sold = 0 ;                      
    double revenue = 0;                            
};

Sales_data & Sales_data::combine(const Sales_data &rhs){  
    units_sold += rhs.units_sold;                         
    revenue += rhs.revenue;

    return *this;                                   
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

inline double Sales_data::avg_price() const {
    return revenue / units_sold;
}

int main(){
    Sales_data book1, book2("c++primer"), book3("discrete mathmatics", 20,10.506), book4(std::cin);
    std::vector<Sales_data> salesVec{book1, book2, book3, book4, Sales_data("cplusplus", 30, 14.54), Sales_data("cplus", 13, 34.45)};

    std::cout << "\nList of books : " << std::endl;
    for( auto book : salesVec){
        print(std::cout, book) << std::endl;
    }

    //  sorts the salesdata vector based on the alphabetical order of isbn
    std::cout << "---------------------------" << std::endl;
    std::sort(salesVec.begin(), salesVec.end(), [](const Sales_data &lhs, const Sales_data &rhs){ return lhs.isbn() < rhs.isbn(); });
    std::cout << "\nsorted list of transactions based on isbn : " << std::endl;
    for(auto book : salesVec){
        print(std::cout , book) << std::endl;
    }

    return 0;
}