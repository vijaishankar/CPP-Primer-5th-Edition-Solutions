/************************************************************************************************************************************************************
 * @file Ex_12_9.cpp
 * @brief Exercise 12.9: Explain what happens in the following code:
 *      int *q = new int(42), *r = new int(100);
 *      r = q;
 *      auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
 *      r2 = q2;
 * @date 2024-01-15
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * int *q = new int(42), *r = new int(100);
 *      q and r are pointers to int, new allcates memory to hold an object of type int and initialises with value 42 in the case of 
 *      q and with value 100 in the case of r
 *              *q == 42,  *r == 100
 * 
 * r = q;
 *      r is assigned the address contained in q, now both r and q points to same memory
 *               q == r
 *              *q == *r == 42
 *      as a result, the memory previously r pointed is leaked, as the program didn't delete the memory associated with r previously
 *      the memory will not be returned to free store untill program ends
 * 
 * auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
 *      q2 and r2 are shared pointers to int, make_shared returns a newly allocated dynamic memory directly initialised with 42 
 *      in the case of q2 and 100 in the case of r2.
 *          *q2 = 42,  *r2 = 100
 *          q2.use_count = 1    // only one pointer points to memory q2 points
 *          r2.use_count = 1    // only one pointer points to memory r2 points 
 * 
 * r2 = q2     
 *      r2 is assigned the address pointed by q2, now both r2 and q2 points to same object
 *      use_count of memory previously r2 pointed becomes zero, so the object is deleted and memory is freed
 *      use_count of memory pointed by q2 has two users now, r and q
 *          q2 == r2
 *         *q2 == *r2 
 *          q2.use_count == r2.use_count == 2 
 *************************************************************************************************************************************************************/

