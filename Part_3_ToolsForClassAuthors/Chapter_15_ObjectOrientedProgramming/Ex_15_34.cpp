/************************************************************************************************************************************************************
 * @file Ex_15_34.cpp
 * @brief Exercise 15.34: For the expression built in Figure 15.3 (p. 638):
 * (a) List the constructors executed in processing that expression.
 * (b) List the calls to rep that are made from cout << q. 
 * (c) List the calls to eval made from q.eval().
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * Query q = Query("fiery") & Query("bird") | Query("wind");
 * q = OrQuery( AndQuery(WordQuery("fiery"),WordQuery("bird")), WordQuery("wind"));
 * 
 *(a) List the constructors executed in processing that expression.
 * 1. WordQuery(const std::string &word) to build WordQuery object for string "fiery".
 * 2. WordQuery(const std::string &word) to build WordQuery object for string "bird".
 * 3. WordQuery(const std::string &word) to build WordQuery object for string "wind".
 * 4. AndQuery constructor that takes two QueryObjects will be run for WordQuery objects "fiery" and "bird"
 * 5. OrQuery constructor that takes two QueryObjects will be run for AndQuery object and WordQuery object for "wind". 
 * 
 *(b) List the calls to rep that are made from cout << q.
 *      output stream operator will call q.rep() which is a non-virtual function, which will in-turn calls the virtual 
 * function of the corresponding type.
 * cout << q 
 * q.rep() ->  OrQuery::rep() -> ( AndQuery::rep(), Query::rep())
 *    
 *    AndQuery::rep() -> Query::rep(), Query::rep() ->  WordQuery::rep() for "fiery" , WordQuery::rep() for "bird"
 *    
 *    WordQuery::rep() for "wind"
 * 
 *
 *(c) List the calls to eval made from q.eval() :
 *    q.eval() ->  OrQuery::eval() -> ( AndQuery::eval(), Query::eval())
 *    
 *    AndQuery::eval() -> Query::eval(), Query::eval() ->  WordQuery::eval() for "fiery" , WordQuery::eval() for "bird"
 *    
 *    WordQuery::eval() for "wind"
 *   
 *    

 *************************************************************************************************************************************************************/



