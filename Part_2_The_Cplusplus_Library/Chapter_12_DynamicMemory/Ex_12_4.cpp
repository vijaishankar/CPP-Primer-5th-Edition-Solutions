/************************************************************************************************************************************************************
 * @file Ex_12_4.cpp
 * @brief Exercise 12.4: In our check function we didn’t check whether i was greater than zero. Why is it okay to omit that
 * check?
 * @date 2024-01-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * there is no need to check as 'i' is std::vector<std::string>::size_type which is unsigned, so even if negative argument is 
 * passed, it will be converted to +ve resulting in 'i' being greater than 0 always.
 * 
 *************************************************************************************************************************************************************/

