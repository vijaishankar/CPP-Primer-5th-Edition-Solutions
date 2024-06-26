/************************************************************************************************************************************************************
 * @file Ex_9_10.cpp
 * @brief Exercise 9.10: What are the types of the following four objects?
          vector<int> v1;
          const vector<int> v2;
          auto it1 = v1.begin(), it2 = v2.begin();
          auto it3 = v1.cbegin(), it4 = v2.cbegin();
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/**
 *  (a) v1.begin()  : std::vector<int>::iterator
 *  (b) v2.begin()  : std::vector<int>::const_iterator
 *  (c) v1.cbegin() : std::vector<int>::const_iterator
 *  (d) v2.cbegin() : std::vector<int>::const_iterator
 * 
 *   as v1.begin() and v2.begin() are different types, the declarations should be in seperate statements, so the correct form
 *   auto it1 : std::vector<int>::iterator
 *   auto it2 = v2.begin() , it3 = v1.cbegin(), it4 = v2.cbegin();
*/

