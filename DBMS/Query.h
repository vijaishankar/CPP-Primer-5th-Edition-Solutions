/************************************************************************************************************************************************************
 * @file Query.h
 * @brief all classes related Database queries
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <utility>
#include <stack>
#include <set>
#include "Table.h"

using std::string; using std::vector; using std::queue; using std::pair; 
using std::set; using std::stack;
typedef pair<bool,string> error_type;

class QueryResult;
class Table;

class QueryBase {
    friend class Query;
    protected :
        virtual QueryResult eval(QueryResult &qr) = 0;
        virtual string res() = 0;
    public :
        virtual ~QueryBase() = default;
};

class QueryResult {
    friend class SqlParser;
    friend class Order_by;
    friend class Select;
    friend class Where;
    friend class NotQuery;
    friend class AndQuery;
    friend class OrQuery;
    friend QueryResult order_by(QueryResult qr, bool desc);
    friend std::iostream & operator<<(std::iostream & os, QueryResult &qr);
    public :
        QueryResult() = default;
        QueryResult(const error_type &e);
        QueryResult(Table &tb, Table &og_);
        QueryResult(Table *tb_, Table &og_); 
    private :
        Table tb;
        Table original;
        error_type error = {false, ""};
};

std::ostream & operator<<(std::ostream & os, QueryResult &qr);

class From {
    public :
        From(const vector<string> &file_lst);
        From(Table &tb_); 
        QueryResult eval() ;
        string res();

    private :
        vector<Table> tb_lst;
        vector<error_type> tb_error;
};

class Query {
    friend Query  operator&(const Query &lhs, const Query& rhs);
    friend Query  operator|(const Query &lhs, const Query& rhs);
    friend Query  operator~(const Query &lhs);
    public :
        Query(const Table::constraint &item, const string & op_);
        Query(QueryBase * q);

        QueryResult eval(QueryResult &qr);
        string res();
    private :
        std::shared_ptr<QueryBase> qb_ptr;
};

class Where : public QueryBase {
    public :
        Where();
        Where(const Table::constraint &, const string &op_);
        QueryResult eval(QueryResult &)override;
        string res()override;
    protected :
        Table::constraint item;
        bool all = false;
        string op;
        error_type error;
};

class BinaryQuery : public QueryBase {
    public : 
        BinaryQuery(const Query &lhs, const Query &rhs, const string &op);
        QueryResult eval(QueryResult &) = 0;
        string res() override;  
    
    protected :
        Query lhs;
        Query rhs;
        string operand;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &lhs, const Query &rhs);
    public :
        AndQuery(const Query &lhs, const Query &);
        QueryResult eval(QueryResult &qr) override;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &lhs, const Query &rhs);
    public : 
        OrQuery(const Query &lhs, const Query &rhs);
        QueryResult eval(QueryResult &qr) override;
};

class NotQuery : public QueryBase {
    friend Query operator~(const Query &q);
    public :
        NotQuery(const Query &source);
        QueryResult eval(QueryResult &qr_) override;
        string res() override; 
    private :
        Query q;
};


QueryResult order_by(QueryResult qr, bool desc);


class Select : public QueryBase{
    public :
        Select(const vector<string> &col_lst_);
        QueryResult eval(QueryResult &qr) override ;
        string res() override;
    private :   
        std::vector<string> col_lst;
        error_type error = {false, ""};
};

class Order_by {
    public :
        Order_by(const vector<pair<string, bool>> &order_list_);
        QueryResult eval(QueryResult qr);
    private :
        vector<pair<string, bool>> order_list;
        bool asc = true;
        error_type error = {false, ""};
};

string str_upper(string str);

class SqlParser {
    public :
        SqlParser(const vector<string> &lst, Table &tb_);
        QueryResult eval();
        QueryResult res();
        static set<string> keywords;
    private :
        typedef pair<bool, string> error_type;

        vector<string> sql_query;
        vector<string> select_lst;
        vector<string> table_lst;
        vector<string> file_lst;
        stack<Query> query_stck;
        vector<pair<string, bool>> order_lst;

        Table tb;

        string error_msg;
        error_type s_error{false, ""};
        error_type f_error{false, ""};
        error_type w_error{false, ""};
        error_type o_error{false, ""};
        bool where_clause = false;
        bool order_clause = false;
        static bool check(const string &str);
};

#endif


