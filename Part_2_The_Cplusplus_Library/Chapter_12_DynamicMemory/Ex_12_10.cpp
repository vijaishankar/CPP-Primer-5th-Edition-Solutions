/************************************************************************************************************************************************************
 * @file Ex_12_10.cpp
 * @brief Exercise 12.10: Explain whether the following call to the process function defined on page 464 is correct. If not,
 * how would you correct the call? 
 *      shared_ptr<int> p(new int(42)); 
 *      process(shared_ptr<int>(p));
 * @date 2024-01-16
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/**
 * - first we are creating a shared_ptr p with built-in pointer returned by new, so now use_count is 1
 * - then we are creating temporary shared_ptr directly initialised with p, as the argument to process, now use_count is 2
 * - then parameter of process which is shared_ptr will be initialised with the temperory shared_ptr, now the use_count is 3
 * - once process fuction's bock ends, the parameter shared_ptr will be destroyed, use_count is decremented to 2
 * - then as the expression in which call operator appears ends, temporary shared_ptr is destroyed, use_count is decremented to 1a
 *          though everything works as expected, it is unnessary to create a temporary shared_ptr, as we can directly pass the
 * shared_ptr p.
 * 
*/