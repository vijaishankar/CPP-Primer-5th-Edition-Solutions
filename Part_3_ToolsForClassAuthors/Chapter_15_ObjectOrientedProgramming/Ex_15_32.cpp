/************************************************************************************************************************************************************
 * @file Ex_15_32.cpp
 * @brief Exercise 15.32: What happens when an object of type Query is copied, moved, assigned, and destroyed?
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * since we din't define any copy-control members, they will be synthesised for Query class. So when an object is copied,
 * move, assigned and destroyed, the respective synthesised copy-control member will be called, which will inturn use
 * Shared_ptr's copy control members.
 * 
 * copied : shared_ptr will be copied to the new object shared_ptr, so both will be pointing to the same address, so the
 * use_count of the shared_ptr will be incremented by one.
 * 
 * moved : pointer in the shared_ptr of the old object will be moved to the new object, so the use_count of the shared_ptr
 * will be 1, meaning there is only one user to the pointed object, the shared_ptr in the old object will be assigned with
 * nullptr;
 * 
 * copy-assigned : same as being copied
 * 
 * move-assignment : same as being moved
 * 
 * destructor : when destructor is run, it will run the shared_ptr destructor which reduces the use_count by 1, if the
 * use_count is 0, it destroys the object pointed by Shared_ptr
 *************************************************************************************************************************************************************/