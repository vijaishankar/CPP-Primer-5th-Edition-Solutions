/************************************************************************************************************************************************************
 * @file Ex_15_41.cpp
 * @brief Exercise 15.41: Reimplement your classes to use built-in pointers to Query_base rather than shared_ptrs. 
 * Remember that your classes will no longer be able to use the synthesized copy-control members.
 * @date 2024-02-08
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#include "TextQuery.cpp"
#include <iostream>
#include <memory>

// abstract class to represent different types of queries, And, Not, Or, WordQuery
class Query_base {
    friend class Query;
    private :
        // virtual functions when called type specific version will run
        virtual QueryResult eval(const TextQuery &query) const = 0;
        virtual std::string rep() const = 0;
        virtual Query_base * clone() const = 0;

    protected :
        virtual ~Query_base() = default;
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

        ~Query() {
            delete q;
        } 

        Query(const Query &source) : q(source.q->clone()) {}
        Query(Query &&source) : q(source.q) {
            source.q = nullptr;
        }
        Query & operator=(const Query &rhs) {
            Query temp(rhs);
            delete q;
            q = temp.q;
            temp.q = nullptr;

            return *this;
        }

        Query operator=(Query &&rhs) {
            if ( q == rhs.q)
                return *this;
            delete q;
            q = rhs.q;
            rhs.q = nullptr;

            return *this;
        }

    private : 
        //  constructor to construct Query object from a shared pointer to Query_base
        Query(Query_base *q_) : q(q_) {}

        //  data member, a shared_ptr to the Query_base
        Query_base *q;
};


// stores a string, when eval() is called calles TextQuery.query() on the string to get the QueryResult containing line_no
// This is the only class which does the core work of queriying (ie) returning the set line_nos in which the word appears
class WordQuery : public Query_base {
    friend class Query;
    private : 
        // only constructor of this class, which takes a query word
        WordQuery(const std::string & query_word_) : query_word(query_word_) {}

        // queries the Text_Query with the given word
        QueryResult eval(const TextQuery &query) const override {
            std::cout << "QueryResult WordQuery::eval(const TextQuery &query) const override : invoked " << query_word << std::endl;
            return query.query(query_word);
        }   

        //  returns the query_word
        std::string rep() const override {
            std::cout << "std::string WordQuery::rep() const override : invoked" << std::endl;
            return query_word;
        }

        WordQuery * clone() const override{
            return new WordQuery(query_word);
        }

    private :
        std::string query_word;
};

Query::Query(const std::string &query_word_) : q(new WordQuery(query_word_)) {
    std::cout << "Query(const std::string &query_word_) : q(WordQuery(query_word_)) : invoked" << std::endl;
}

// abstract class contains Query objects to represent two operands and operator symbol representing Or or And
class BinaryQuery : public Query_base {
    protected :

        std::string rep() const override {
            return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")" ;     
        }

        BinaryQuery(const Query &l, const Query &r, const std::string &opSym_) 
            : lhs(l), rhs(r), opSym(opSym_) {}

    protected :
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

        OrQuery * clone() const override {
            return new OrQuery(lhs,rhs);
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

        AndQuery * clone() const override {
            return new AndQuery(lhs,rhs);
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

        NotQuery * clone() const override {
            return new NotQuery(q);
        }

        Query q;
};

Query operator~(const Query &q) {
    std::cout << "Query operator~(const Query &q) : invoked" << std::endl;
    return Query(new NotQuery(q));
}

Query operator|(const Query &l, const Query &r) { 
    std::cout << "Query operator|(const Query &l, const Query &r) : invoked" << std::endl;
    return Query(new OrQuery(l,r));
}

Query operator&(const Query &l, const Query &r) {
    std::cout << "Query operator&(const Query &l, const Query &r)" << std::endl;
    return Query(new AndQuery(l,r));
}

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile) {
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    TextQuery tq(ifile);

    Query q = Query("fiery") & Query("bird") | Query("wind");
    auto qr = q.eval(tq);
    std::cout << qr << std::endl;

    return 0;
}