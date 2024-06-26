/************************************************************************************************************************************************************
 * @file Ex_8_6.cpp
 * @brief Exercise 8.6: Rewrite the bookstore program from § 7.1.1 (p. 256) to read its transactions from a file. Pass the
 *        name of the file as an argument to main (§ 6.2.5, p. 218)
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <fstream>

/**
 * Sales_trans.txt contains data in format
 * isbn units_sold price 
 */

struct Sales_data{
    std::string book_no;
    double units_sold;
    double revenue;
};

int main(int argc, char **argv){
    std::ifstream ifile(*(argv + 1));
    if(!ifile){
        std::cerr << "Unable to open file";
        return -1;
    }

    Sales_data total;
    double price;
    if( ifile >> total.book_no >> total.units_sold >> price){         //  condition checks for valid input
        total.revenue = total.units_sold * price;
        Sales_data trans;
        while(ifile >> trans.book_no >> trans.units_sold >> price){  //  transactions are read and processed until eof
            trans.revenue = trans.units_sold * price;
            if( total.book_no == trans.book_no ){
                total.revenue += trans.revenue;
                total.units_sold += trans.units_sold;
            }else{
                std::cout << "\n" << total.book_no << " " << total.units_sold << " " << total.revenue << std::endl;
                total = trans;
            }
        }
        std::cout << "\n" << total.book_no << " " << total.units_sold << " " << total.revenue << std::endl;
    }else{
        std::cerr << "NO INPUT";
        return -1;
    }

    return 0;
}