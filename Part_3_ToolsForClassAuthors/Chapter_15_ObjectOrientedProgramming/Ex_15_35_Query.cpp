/************************************************************************************************************************************************************
 * @file Ex_15_35.cpp
 * @brief Exercise 15.35: Implement the Query and Query_base classes, including a definition of rep but omitting the 
 * definition of eval.
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include "TextQuery.cpp"
#include <iostream>
#include <memory>
#include <vector>

// abstract class to represent different types of queries, And, Not, Or, WordQuery
class Query_base {
    friend class Query;
    private :
        // virtual functions when called type specific version will run
        virtual QueryResult eval(const TextQuery &query) const = 0;
        virtual std::string rep() const = 0;
};

//  Interface class of the queries
class Query {
    friend Query operator~(const Query &q);    //   returns set of lines in which the word didn't appear  
    friend Query operator|(const Query &l, const Query &r);     //  returns Query object pointing to NotQuery object constructed from two Query objects
    friend Query operator&(const Query &l, const Query &r);     //  returns Query object pointing to AndQuery object constructed form two Query objects    
    public : 
        //  Builds a WordQuery object from the string
        Query(const std::string &query_word_);
    
        //  calls virtual function eval of pointed type 
        QueryResult eval(const TextQuery &query) const {
            return q->eval(query);
        }
    
        //  calls virtual function rep of pointed type
        std::string rep() const {
            return q->rep();
        }    
        
        // container to store the history of queries, so that user can access queries from histroy by number and can combine them to form new queries
        // only new queries are added, (ie) when WordQuery is used to construct Query object, and when the !,|,& operators construct new Query on
        static std::vector<Query> history;
    private : 
        //  constructor to construct Query object from a shared pointer to Query_base
        Query(std::shared_ptr<Query_base> q_) : q(q_) {
            history.push_back(*this);
        }

        //  data member, a shared_ptr to the Query_base
        std::shared_ptr<Query_base> q;
};

std::vector<Query> Query::history;

// stores a string, when eval() is called calles TextQuery.query() on the string to get the QueryResult containing line_no
// This is the only class which does the core work of queriying (ie) returning the set line_nos in which the word appears
class WordQuery : public Query_base {
    friend class Query;
    private : 
        // only constructor of this class, which takes a query word
        WordQuery(const std::string & query_word_) : query_word(query_word_) {}

        // queries the Text_Query with the given word
        QueryResult eval(const TextQuery &query) const override {
            return query.query(query_word);
        }   

        //  returns the query_word
        std::string rep() const override {
            return query_word;
        }

    private :
        std::string query_word;
};

Query::Query(const std::string &query_word_) : q(new WordQuery(query_word_)) {
    history.push_back(*this);
}

// abstract class contains Query objects to represent two operands and operator symbol representing Or or And
class BinaryQuery : public Query_base {
    protected :

        std::string rep() const override {
            return "( " + lhs.rep() + " " + opSym + " " + rhs.rep() + " )" ;     
        }

        BinaryQuery(const Query &l, const Query &r, const std::string &opSym_) 
            : lhs(l), rhs(r), opSym(opSym_) {}

        virtual ~BinaryQuery() = default;
        Query lhs, rhs;
        std::string opSym;
};

// class OrQuery which represents the union of the lineno's in both the operands
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &l, const Query &r);
    private :
        OrQuery(const Query &l, const Query &r) 
            : BinaryQuery(l, r, "|") {}
        
        QueryResult eval(const TextQuery &query) const override {
            auto res1 = lhs.eval(query);
            auto res2 = rhs.eval(query);
            std::set<size_t> res_lines(res1.begin(), res1.end());
            res_lines.insert(res2.begin(), res2.end());

            return QueryResult(rep(), res1.get_file(), std::shared_ptr<std::set<size_t>>(new std::set<size_t>(res_lines)));
        } 
};

// class derived from BinaryQuery which returns the intersection of set lineno's in both the operands
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &l, const Query &r);
    private :
        // takes two Query objects representing two operands and constructs its BinaryQuery part with '&' symbol
        AndQuery(const Query &l, const Query &r) 
            : BinaryQuery(l, r, "&") {}
        

        QueryResult eval(const TextQuery &query) const override {
            auto left = lhs.eval(query), right = rhs.eval(query);
            std::set<size_t> res;
            std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(res, res.begin()));
            
            return QueryResult(rep(), left.get_file(), std::shared_ptr<decltype(res)>(new std::set<size_t>(res)));
        }
};

// class that contains a query object, when evaluted, it returns line_no in which the word is not found
class NotQuery : public Query_base {
    friend Query operator~(const Query &q);
    private :   
        // constructor that takes a query object
        NotQuery(const Query &q_) 
            : q(q_) {}


        QueryResult eval(const TextQuery &query) const override{
            auto qr = q.eval(query);
            auto sz = qr.get_file()->size();
            auto beg = qr.begin();
            auto end = qr.end();
            std::set<size_t> res;

            for( size_t i = 0; i < sz ; ++i) {
                if(beg == end || *beg != i ) {
                    res.insert(i);
                } else {
                    ++beg;
                } 
            }

            return QueryResult(rep(), qr.get_file(), std::shared_ptr<decltype(res)>(new decltype(res)(res)));
        }

        std::string rep() const override {
            return "~(" + q.rep() + ")"; 
        }

        Query q;
};

Query operator~(const Query &q) {
    return std::shared_ptr<Query_base>(new NotQuery(q));
}

Query operator|(const Query &l, const Query &r) { 
    return std::shared_ptr<Query_base>(new OrQuery(l,r));
}

Query operator&(const Query &l, const Query &r) {
    return std::shared_ptr<Query_base>(new AndQuery(l,r));
}

