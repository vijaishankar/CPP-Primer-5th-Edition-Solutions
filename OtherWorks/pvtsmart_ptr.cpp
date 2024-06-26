/************************************************************************************************************************************************************
 * @file pvtsmart_ptr.cpp
 * @brief Base template from which smart pointers template will inherit.
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 * *************************************************************************************************************************************************************/ 
#ifndef PVTSMART_PTR_CPP
#define PVTSMART_PTR_CPP

#include <iostream>

template <typename T> class pvtsmart_ptr;   //  forward declaration 
template <typename T> class pvtshared_ptr;

template <typename T> 
void swap(pvtsmart_ptr<T> &, pvtsmart_ptr<T> &);   //  template declaration of swap non-member function

template <typename T>
bool operator==(const pvtsmart_ptr<T> &lhs, const pvtsmart_ptr<T> &rhs);

template <typename T>
bool operator<(const pvtsmart_ptr<T> &lhs, const pvtsmart_ptr<T> &rhs);

template <typename T>  //  pvtsmart_ptr template definition
class pvtsmart_ptr {
    friend void swap<T>(pvtsmart_ptr &lhs, pvtsmart_ptr &rhs);  //  non-member version of swap that swaps the pointers
    friend bool operator==<T>(const pvtsmart_ptr &lhs, const pvtsmart_ptr &rhs);       //  checks for equality
    friend bool operator< <T>(const pvtsmart_ptr<T> &lhs, const pvtsmart_ptr<T> &rhs); //  checks whether the lhs is lesser
    friend class pvtshared_ptr<T>;
    public :
        typedef T element_type;             //  type of the object
        explicit operator bool() const ;    //  conversion from class type to bool.
        T & operator*() const;              //  dereference operator returns non-const lvalue reference.
        T * operator->() const;             //  arrow operator returns the address of the object ptr points.
        T * get();                          //  returns the pointer stored in ptr member
        const T * get() const;              //  returns the const pointer stored in ptr member.
        void swap(pvtsmart_ptr &rhs);       //  swaps the pointers

    protected :
        pvtsmart_ptr();                     //  default constructor.
        pvtsmart_ptr(T *ptr_);              //  constructor that takes a pointer of type T.
        virtual ~pvtsmart_ptr() = default;  //  virtual destructor

        T *ptr;                             //  ptr member that points to type T.
};

template <typename T>
pvtsmart_ptr<T>::pvtsmart_ptr() : ptr(nullptr) {}

template <typename T>
pvtsmart_ptr<T>::pvtsmart_ptr(T *ptr_) : ptr(ptr_) {}

template <typename T>
inline pvtsmart_ptr<T>::operator bool() const {    // conversion from class type to bool
    return ptr ? 1 : 0;
}

template <typename T>
inline T & pvtsmart_ptr<T>::operator*() const {  //  Dereferencing returns a non-const reference. const qualification only makes the ptr const
    return *ptr;
}

template <typename T>
inline T * pvtsmart_ptr<T>::operator->() const {  //  Arrow operator returns the address of the object ptr points
    return ptr;
}

template <typename T>
inline T * pvtsmart_ptr<T>::get() {
    return ptr;
}

template <typename T>
inline const T * pvtsmart_ptr<T>::get() const {   //  returns the pointer in ptr;
    return ptr;
}

template <typename T> 
void pvtsmart_ptr<T>::swap(pvtsmart_ptr &rhs) {
    using std::swap;
    swap(ptr, rhs.ptr);
}


template <typename T>
inline void swap(pvtsmart_ptr<T> &lhs, pvtsmart_ptr<T> &rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.count, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template <typename T>
bool operator==(const pvtsmart_ptr<T> &lhs, const pvtsmart_ptr<T> &rhs) {
    return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator<(const pvtsmart_ptr<T> &lhs, const pvtsmart_ptr<T> &rhs) {
    return lhs.ptr < rhs.ptr;
}

#endif