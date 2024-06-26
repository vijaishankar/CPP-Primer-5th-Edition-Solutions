/************************************************************************************************************************************************************
 * @file Ex_16_18.cpp
 * @brief Exercise 16.18: Explain each of the following function template declarations and identify whether any are 
 * illegal. Correct each error that you find.
 * (a) template <typename T, U, typename V> void f1(T, U, V);
 * (b) template <typename T> T f2(int &T);
 * (c) inline template <typename T> T foo(T, unsigned int*);
 * (d) template <typename T> f4(T, T);
 * (e) typedef char Ctype;
 *     template <typename Ctype> Ctype f5(Ctype a);
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * (a) template <typename T, U, typename V> void f1(T, U, V);  // error : U should be explicitly declared as type or non-type parameter
 * (b) template <typename T> T f2(int &T);    //  error : T is a type name, typenames cannot be used as function parameter names
 * (c) inline template <typename T> T foo(T, unsigned int*);  //  error : inline should come after template parameter list
 * (d) template <typename T> f4(T, T);  //  error : return type must be mentioned
 * (e) typedef char Ctype;  
 *     template <typename Ctype> Ctype f5(Ctype a);  ok : the type parameter name Ctype hides the previous declaration in the outside scope.
 *************************************************************************************************************************************************************/
