/************************************************************************************************************************************************************
 * @file Ex_13_41.cpp
 * @brief Exercise 13.41: Why did we use postfix increment in the call to construct inside push_back? What would happen if it
 * used the prefix increment?
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * first_free points the first free memory(unconstructed) in the memory allocated, so when we use post_increment, first_free will be
 * incremented to point next free memory, and its old value(previous free memory) will be returned, which will be passed to construct
 * the new element. So construction happens at next free memory and first_free now points to next free as expected.
 *      If we have use the prefix increment, first_free will be incremented first, and then construction happens at memory pointed
 * by incremented first_free, as a result a block of memory will be wasted every time we add an element, which is not we want.
 * 
 *************************************************************************************************************************************************************/