/************************************************************************************************************************************************************
 * @file Database.cpp
 * @brief main interface of the DBMS
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include "Table.h"
#include "Query.h"
#include <iterator>
#include <map>
#include <fstream>
#include <limits>


using std::vector; using std::string; using std::map; using std::pair;
std::string prompt("sql[ 0 to submit SELECT ] > ");
std::string err_prompt(prompt + "error : ");

void query_table(Table &tb);
void display_help();
Table * create_table();
void save_to_file(Table &tb, const std::string &ifile_name, bool clear_file = false);
void clear_cin();

int main() {
    std::set<std::string> first{"SELECT","CREATE","ADD", "DELETE", "EXIT","HELP","DELETE","SAVE","OPEN"};
    std::vector<std::string> sql_query;
    bool table_exist = false;
    Table *tb = nullptr;
    std::fstream iofile;
    std::string iofile_name;
    bool file_exist = false;
    std::cout << "SQL commands supported : \nADD CREATE DELETE EXIT SAVE SELECT" << std::endl;
    while (1) {
        std::cout << prompt;
        string cmd1, cmd2;
        std::cin >> cmd1;
        cmd1 = str_upper(cmd1);
        if (first.find(cmd1) == first.end()) {
            std::cerr << err_prompt << " command doesn't exist, type HELP" << std::endl;
            clear_cin();
            continue;
        }

        if (cmd1 == "CREATE") {
            std::cin >> cmd2;
            cmd2 = str_upper(cmd2);
            if (!table_exist) { 
                tb = create_table();
                if (tb) {
                    table_exist = true;
                } else {
                    std::cerr << err_prompt << "unable to open table" << std::endl;
                }
            } else {
                std::cerr << err_prompt << "Table is already open" << std::endl;
            }  
            clear_cin();
        }

        if (cmd1 == "SELECT") {
            if (table_exist) {
                query_table(*tb);
            } else {
                std::cerr << err_prompt << "no table exist" << std::endl;
                clear_cin();
            }
        }

        if (cmd1 == "ADD") {
            if (table_exist) {
                add_record(*tb);
            } else {
                std::cerr << err_prompt << "Table need to be created" << std::endl;   
            }
            clear_cin();
        }

        if (cmd1 == "EXIT") {
            return 0;
        }

        if (cmd1 == "DELETE") {
            if (table_exist) {
                string p_key, val, op;
                std::cin >> p_key >> op >> val;
                auto count = tb->remove_record({p_key, val});
                if (count) {
                    std::cout << "record deleted" << std::endl;
                }
            }
            clear_cin();
        }

        if (cmd1 == "SAVE") {
            if (table_exist) {
                if (!file_exist) {    
                    std::cout << "file name : ";
                    std::cin >> iofile_name;
                }   
                if (tb->is_modified()) {
                    save_to_file(*tb, iofile_name, true); 
                } else {
                    save_to_file(*tb, iofile_name);
                }    
            } 
            clear_cin();      
        }

        if (cmd1 == "HELP") {
            display_help();
            clear_cin();
        }

        if (cmd1 == "OPEN") {
            std::cin >> cmd2;
            iofile.open(cmd2, std::fstream::ate | std::fstream::in | std::fstream::out);
            if (!iofile) {
                std::cerr << err_prompt << "Unable to open file" << std::endl;
                clear_cin();
                continue;
            } 
            file_exist = true;
            iofile_name = cmd2;
            iofile.seekg(std::fstream::beg);
            delete tb;
            tb = new Table(iofile);
            std::cout << cmd2 << " opened succefully" << std::endl;
            std::cout << tb->get_name() << " table is built from " << cmd2 << std::endl;
            table_exist = true;
            clear_cin();
        }
    }
}

void display_help() {
    std::map<string, string> syntax_dict{ {{"CREATE"}, {"CREATE <table_name> \ncreates a table with table name as table_name"}},
                                          {{"SELECT"}, {"SELECT <col_name1>, <col_name2> ...\ndisplays the records with col_name1 and col_name2 from the table, SELECT * refers to all coloumns"}},
                                          {{"FROM"}, {"FROM <table_name> \nfetches the records from table table_name"}},
                                          {{"WHERE"}, {"WHERE <constraint> \nfilters the records which matches the constraint"}},
                                          {{"AND"}, {"<constraint1> AND <constraint2>\ncontains only records matches both the constraint"}},
                                          {{"OR"}, {"<constraint1> OR <constraint2>\ncontains records which matches either or the other constraint"}},
                                          {{"NOT"}, {"NOT <constraint>\ncontains records that doesn't match the constraint"}},
                                          {{"CONSTRAINT"}, {"<col_name> <operator> <value>\na record is a match if the operator returns true for the value in the specified coloumn"}},
                                          {{"OPERATOR"}, {"=, equality \n!=, in-equality \n<, less than \n>, greater than \n<=, less than or equal to \n>=, greater than or equal to"}},
                                          {{"ORDER_BY"}, {"ORDER_BY <col_name> DESC \nsorts the records based on the values in col_name.\n\tDESC is optional, makes the sorting in descendant order"}},
                                          {{"CLOSE"}, {"CLOSE <file_name>\ncloses the file named file_name"}},
                                          {{"OPEN"}, {"OPEN <file_name>\nopens the file named file_name"}},
                                          {{"DELETE"}, {"DELETE <table_name>\ndeletes the table"}},
                                          {{"EXIT"}, {"exits the program"}},
                                          {{"SAVE"}, {"saves the table to file"}},
                                          {{"SAVE_AS"},{"saves the table to new file"}}
                                        };

    std::string cmd1;
    std::cin >> cmd1;
    if (str_upper(cmd1) == "ALL") {
        for(auto iter = syntax_dict.begin(); iter != syntax_dict.end(); ++iter) {
            std::cout << iter->first << " ";
        }
        return;
    }

    if(syntax_dict.find(str_upper(cmd1)) != syntax_dict.end()) {
        std::cout << syntax_dict[str_upper(cmd1)] << std::endl;
    } else {
        std::cout << cmd1 << " is not an acceptable command, to display the list of accepted cmds use HELP ALL" << std::endl;
    }
    return;                   
}

Table * create_table() {

    string tbname;
    std::cin >> tbname;

    Table::schema_type schema;
    string p_key;
    create_schema(schema, p_key);
    return new Table(schema, p_key, tbname);
}

void save_to_file(Table &tb, const std::string &file_name, bool clear_file) {
    std::fstream iofile;
    if (clear_file) {
        iofile.open(file_name, std::fstream::trunc | std::fstream::out | std::fstream::in);
    } else {
        iofile.open(file_name, std::fstream::ate | std::fstream::out | std::fstream::in);
    }    

    if (!iofile) {
        std::cerr << err_prompt << "unable to save file, try again" << std::endl;
        return;
    } 

    iofile << tb;
    std::cout << prompt << file_name << " saved successfully" << std::endl;

    iofile.close();
    return; 
}

void clear_cin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();  
}

void query_table(Table &tb) {
    string word;
    vector<string> q_lst;
    while (std::cin >> word && word[0] != '0') {
        string up_word = str_upper(word);
        if (SqlParser::keywords.find(up_word) != SqlParser::keywords.end()) {
            q_lst.push_back(up_word);
        } else {
            q_lst.push_back(word);
        }    
    }
    SqlParser s1(q_lst, tb);
    s1.eval();

    return;
}
 