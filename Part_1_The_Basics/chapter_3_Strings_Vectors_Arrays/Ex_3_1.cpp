//  Exercise 3.1: Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76) with appropriate using declarations.
//  ######################################################################################################################
/*
//  Exercise 1.9: Write a program that uses a while to sum the numbers from 50 to 100
#include <iostream>
using std::cin; using std::cout; using std::endl;

int main(){
    size_t sum = 0;
    int val = 50;
    
    while( val <= 100){
        sum += val;
        ++val;
    }
    cout << "the sum of numbers 50 to 100 : " << sum << endl;
    return 0;
}
// -----------------------------------------------------------------------------------------------------------------------
*/

/*  Exercise 1.10: In addition to the ++ operator that adds 1 to its operand, there is a decrement operator (--) that 
    subtracts 1. Use the decrement operator to write a whilethat prints the numbers from ten down to zero.*/
/*
    #include <iostream>
    using std::cout; using std::cin; using std::endl;

    int main(){
        int val = 10;

        while( val >= 0){
            cout << val << " ";
            --val;
        }
        cout << endl;
        return 0;
    }
*/
//  -----------------------------------------------------------------------------------------------------------------------
/*  Exercise 1.11: Write a program that prompts the user for two integers. Print each number in the range specified by
 *  those two integers.*/
/*
#include <iostream>
using std::cout; using std::cin; using std::endl;

int main(){
    cout << "Enter two numbers to print the range of numbers in-between : \n";
    int beg, end;
    cin >> beg >> end;

    while( beg <= end ){
        cout << beg << " ";
        ++beg;
    }
    cout << endl;

    return 0;
}
*/

/*  Exercise 2.41: Use your Sales_data class to rewrite the exercises in § 1.5.1 (p. 22),§ 1.5.2 (p. 24), and § 1.6 (p. 25).
    For now, you should define your Sales_data class in the same file as your main function.*/

/*  Exercise 1.20 : write a program that reads a set of book sales transactions, writing each transaction to the standard 
 *  output. */
/*
#include <iostream>
#include <string>
#include "Sales_data.h"
using std::cout; using std::cin; using std::endl;

int main(){
    Sales_data book1, book2;
    cout << "Enter a set of book sales transactions : \n";
    double price;
    cin >> book1.book_no >> price >> book1.units_sold;
    book1.revenue = price * book1.units_sold;
    cin >> book2.book_no >> price >> book2.units_sold;
    book2.revenue = price * book2.units_sold;

    cout << book1.book_no << " " << book1.units_sold << " " << book1.revenue << endl; 
    cout << book2.book_no << " " << book2.units_sold << " " << book2.revenue << endl;

    return 0;
} 
*/
//  -----------------------------------------------------------------------------------------------------------------------
/*  Exercise 1.21: Write a program that reads two Sales_item objects that have the same ISBN and produces their sum.*/

#include <iostream>
#include <string>
#include "Sales_data.h"
using std::cout; using std::cin; using std::endl; using std::cerr;
/*
int main(){
    Sales_data book1, book2;
    cout << "Enter a set of book sales transactions : \n";
    double price;
    cin >> book1.book_no >> price >> book1.units_sold;
    book1.revenue = price * book1.units_sold;
    cin >> book2.book_no >> price >> book2.units_sold;
    book2.revenue = price * book2.units_sold;

    if( book1.book_no == book2.book_no ){
        cout << book1.book_no << " " << book1.units_sold + book2.units_sold << " " << book1.revenue + book2.revenue << endl;
        return 0;
    }else{
        cerr << "ISBN should match" << endl;
        return -1;
    }
  
}
*/
//  ----------------------------------------------------------------------------------------------------------------------
/*  Exercise 1.22: Write a program that reads several transactions for the same ISBN .Write the sum of all the transactions
 *  that were read */
/*
int main(){
    Sales_data temp, total;
    cout << "Enter the list of transactions : " << endl;
    double price;
    cin >> total.book_no >> price >> total.units_sold;
    total.revenue = price * total.units_sold;

    while(cin >> temp.book_no >> price >> temp.units_sold ){
        temp.revenue = price * temp.units_sold;
        if( total.book_no == temp.book_no ){
            total.revenue += temp.revenue;
            total.units_sold += temp.units_sold;
        }else{
            cout << total.book_no << " " << total.units_sold << total.revenue << endl;
            return 0;
        }
    } 
    cout << total.book_no << " " << total.units_sold << total.units_sold << endl;

    return 0;
}
*/
//  ---------------------------------------------------------------------------------------------------------------------
//  Exercise 1.23: Write a program that reads several transactions and counts how many transactions occur for each ISBN
/*  
int main(){
    Sales_data prev, curr;
    cout << "Enter the list of transactions : ";
    double price;
    cin >> prev.book_no >> price >> prev.units_sold;
    prev.revenue = price * prev.units_sold;
    int count = 1;
    while(cin >> curr.book_no >> price >> curr.units_sold){
        curr.revenue = price * curr.units_sold;
        if( prev.book_no == curr.book_no ){
            ++count;
        }else{
            cout << prev.book_no << " occurs " << count << endl;
            prev = curr;
            count = 1;
        }
    }
    cout << prev.book_no << " occurs " << count << endl;
    return 0;
}
*/

/*  Exercise 1.25: Using the Sales_item.h header from the Web site, compile and execute the bookstore program presented
 *  in this section. */

int main(){

    Sales_data total, book;
    double price;
    cout << "Enter the list of transactions : \n";
    
    if( cin >> total.book_no >> price >> total.units_sold ){
        total.revenue = price * total.units_sold;
        while( cin >> book.book_no >> price >> book.units_sold ){
            book.revenue = price * book.units_sold;
            if( total.book_no == book.book_no ){
                total.revenue += book.revenue;
                total.units_sold += book.units_sold;
            }else{
                cout << total.book_no << " " << total.units_sold << " " << total.revenue << endl;
                total = book;
            }
        }
        cout << total.book_no << " " << total.units_sold << " " << total.revenue << endl;
        return 0;
    }else{
        cerr << "No input" << endl;
        return -1;
    }
}
