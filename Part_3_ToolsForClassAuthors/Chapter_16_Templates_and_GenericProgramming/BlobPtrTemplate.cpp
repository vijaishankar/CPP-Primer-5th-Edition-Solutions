/************************************************************************************************************************************************************
 * @file BlobPtrTemplate.cpp
 * @brief Pointer Template to Blob Template, will be used to creater iterators to the Blob Containers.
 * @date 2024-02-11
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#ifndef BLOBPTR_H
#define BLOBPTR_H

#include <memory>
#include <iostream>
#include <vector>
#include "BlobTemplate.cpp"

template<typename> class BlobPtr;
template <typename T> 
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
template <typename> class Blob;

template <typename T>
class BlobPtr {
    friend bool operator==<T> (const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
    friend class Blob<T>;
    public :
        typedef typename std::vector<T>::size_type size_type;
        
        // constructors
        BlobPtr() : w_ptr(nullptr), curr(0) {}
        BlobPtr(Blob<T> &b, size_type curr_) : w_ptr(b.data), curr(curr_) {}

        // container access members
        T & operator*() {
            auto p = check(curr, "dereferencing past end");
            return (*p)[curr];  
        } 

        const T & operator*() const {
            auto p = check(curr, "dereferencing past end");
            return (*p)[curr];
        }

        T & operator[](size_type i) {
            return *(check(i, "out of bounds"))[i];
        }

        const T & operator[](size_type i) const {
            *(check(i, "out of bounds"))[i];
        }

        BlobPtr& operator++() {
            check(curr, "out of bounds");
            ++curr;
            return *this;
        }

        BlobPtr& operator--() {
            check(curr, "out of bounds");
            if (!curr)
                throw std::runtime_error("out of bounds");
            --curr;
            return *this;
        }

        BlobPtr operator++(int) {
            auto ret = *this;
            ++*this;
            return ret;
        };

        BlobPtr operator--(int) {
            auto ret = *this;
            --*this;
            return ret;
        }

    private :
        //  data members
        std::weak_ptr<std::vector<T>> w_ptr;
        size_type curr;

        //  private utility
        std::shared_ptr<std::vector<T>> check(size_type i, const std::string &msg) {
            auto p = w_ptr.lock();
            if (!p) {
                throw std::runtime_error("non-existent object");
            }

            if(curr >= p->size()) {
                throw std::runtime_error(msg);
            }

            return p;
        }
        
};

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
        return lhs.w_ptr.lock() == rhs.w_ptr.lock() && lhs.curr == rhs.curr;
}

#endif