/************************************************************************************************************************************************************
 * @file Ex_16_60.cpp
 * @brief Exercise 16.60: Explain how make_shared (§ 12.1.1, p. 451) works.
 * @date 2024-02-17
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * std::make_shared<T>(args);
 * make_shared is a function template 
 * T : explicit parameter to denote the type for which memory should be allocated
 * args : varriying list of no or types of arguments, which will be passed to the constructor of type T
 * template with 1st parameter bound to T and a template parameter pack denoting the types in args is used to instantiate the make_shared function
 * with 1st argument of type T, function parameter pack consisting of the arguments passed in the call with pattern of rvalue reference
 * constructor of the type T will be called with expanded argument pack. 
 * std::forward will be used to get the original types of the arguments int the pack.
 * finally returns a shared_pointer pointing to the constructed object.
 * // definition of std::make_shared will be similar to this
 * 
 * template <tyepname T, typename... Args>
 * shared_ptr<T> make_shared(Args&&... args) {
 *      T *p = new T;
 *      std::construct_at(p, std::forward<Args>(args)...)
 * 
 *      return shared_ptr(p);
 * }
 * 
 * 
 * 
 *************************************************************************************************************************************************************/