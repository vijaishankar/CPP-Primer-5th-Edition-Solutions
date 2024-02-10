/************************************************************************************************************************************************************
 * @file Ex_12_33.cpp
 * @brief Exercise 12.33: In Chapter 15 we’ll extend our query system and will need some additional members in the QueryResult
 * class. Add members named begin and end that return iterators into the set of line numbers returned by a given query, and a
 * member named get_file that returns a shared_ptr to the file in the QueryResult object.
 * @date 2024-01-19

 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string; using std::vector; using std::map; using std::set; using std::shared_ptr; using std::make_shared; using std::cout; using std::cin;
using std::ifstream; using std::istringstream; using std::ofstream; using std::ostream; using std::endl;

class QueryResult;
class TextQuery{
    public :
        typedef vector<string>::size_type index_type;

        TextQuery(ifstream &file_strm) : file(make_shared<vector<string>>()) {
            string line;
            index_type line_no = 0;
            while(getline(file_strm, line)){
                file->push_back(line);
                istringstream line_strm(line);
                string word;
                
                while(line_strm >> word){
                    if(!isalpha(word[0])) {
                        word.erase(word.begin());
                    }
                    if(!isalpha(word[word.size() - 1])){
                        word.erase(word.end() - 1);
                    }
                    auto &l_set = word_map[word];
                    if(!l_set){
                        l_set.reset(new set<index_type>);
                    }
                    l_set->insert(line_no);
                }
                ++line_no;
            }
        }
        QueryResult query(const string &sought_word) const ;
    private :
        shared_ptr<vector<string>> file;
        map<string, shared_ptr<set<index_type>>> word_map;
};

class QueryResult{
    friend inline ostream & print(ostream &out, const QueryResult &qr);
    public :
        using index_type = TextQuery::index_type;
       
        QueryResult(const string &word_param, shared_ptr<vector<string>> file_param, shared_ptr<set<index_type>> lines_param) 
                : word(word_param), file(file_param), lines(lines_param) {}

        set<index_type>::iterator begin(){
            return lines->begin();
        }

        set<index_type>::iterator end(){
            return lines->end();
        }

        shared_ptr<vector<string>> get_file(){
            return file;
        }
    private :   
        string word;
        shared_ptr<vector<string>> file;
        shared_ptr<set<index_type>> lines;            
};

QueryResult TextQuery::query(const std::string &sought_word) const {
    static shared_ptr<set<index_type>> no_data(make_shared<set<index_type>>());
    auto result = word_map.find(sought_word);
    if(result == word_map.end()){
        return QueryResult(sought_word, file, no_data);
    }else{
        return QueryResult(sought_word, file, result->second);
    }
}

string make_plural(set<TextQuery::index_type>::size_type n){
    return n > 1 ? " times " : " time ";
}

ostream & print(ostream &out, const QueryResult &qr){
    auto n = qr.lines->size();
    out << qr.word << " appears " << n << make_plural(n) << "in the file" << endl; 
    for(auto line_no : *qr.lines){
        out << "[ " << line_no + 1 << " ]  " << *(qr.file->begin() + line_no) << endl;
    }

    return out;
}

void runQueries(ifstream& infile)
{
    TextQuery tq(infile); 
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile){
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    runQueries(ifile);

    return 0;
}