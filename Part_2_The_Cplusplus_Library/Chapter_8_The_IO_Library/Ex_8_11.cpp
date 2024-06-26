/************************************************************************************************************************************************************
 * @file Ex_8_11.cpp
 * @brief Exercise 8.11: The program in this section defined its istringstream object inside the outer while loop. What changes
 *        would you need to make if record were defined outside that loop? Rewrite the program, moving the definition of record
 *        outside the while, and see whether you thought of all the changes that are needed.
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/**
 * changes :
 *    # if record were defined outside the loop, each time we extract all data from the record, the failbit and eofbit will be 
 *      set in record.
 *    # though we can bind a new line in to the record, we won't be able to read from it entill the error states are cleared
 *    # so before we reuse the record to extract, we use record.clear()
 *    # on declaring inside the loop, the record obj gets destroyed and created every time the loop iterates, so we doesn't
 *      error states.    
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

int main()
{
    std::string line, word; // will hold a line and word from input, respectively
    std::vector<PersonInfo> people; // will hold all the records from the input
    // read the input a line at a time until std::cin hits end - of - file(or another error) 
    std::istringstream record; // bind record to the line
    while (getline(std::cin, line))
    {
        PersonInfo info; // create an object to hold this record’s data
        record.str(line);
        record >> info.name; // read the name
        while (record >> word) // read the phone numbers
            info.phones.push_back(word); // and store them
        people.push_back(info); // append this record to people
        record.clear();  // clears eofbit and failbit in the strm
    }

    for(auto iter = people.cbegin(); iter != people.cend(); ++iter){
        std::cout << (*iter).name << " ";
        for(auto it = (*iter).phones.cbegin() ; it != (*iter).phones.end(); ++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}