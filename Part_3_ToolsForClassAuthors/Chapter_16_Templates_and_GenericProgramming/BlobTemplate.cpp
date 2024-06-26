/************************************************************************************************************************************************************
 * @file BlobTemplate.cpp
 * @brief template type to define containers to various type.
 * @date 2024-02-11
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#ifndef BLOB_H
#define BLOB_H

#include <iostream>
#include <vector>
#include <memory>
#include <initializer_list>
#include "BlobPtrTemplate.cpp"

template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T> &lhs, const Blob<T> &rhs);

template <typename T>
class Blob {
    friend bool operator==<T> (const Blob<T> &lhs, const Blob<T> &rhs);

    friend class BlobPtr<T>;
    public :
        // typedef's
        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;

        //  constructor 
        Blob() : data(std::make_shared<std::vector<T>>()) {}
        Blob(const std::initializer_list<T> &il) : data(std::make_shared<std::vector<T>>(il)) {}

        template <typename It> 
        Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b,e)) {}

        // size related members
        size_type size() const {
            return data->size();
        }

        bool empty() const {
            return data->empty();
        } 

        // container modifications 
        void push_back(const T &item) {
            data->push_back(item);
        }

        void push_back(T &&item) {
            data->push_back(std::move(item));
        }

        void pop_back() {
            check(0, "pop_back() on a empty container");
            data->pop_back();
        }

        T& back() {
            check(0, "back() on a empty container");
            return data->back();
        }

        const T& back() const {
            check(0, "back() on a empty container");
            return data->back();
        }

        T& front() {
            check(0, "front() on a empty container");
            return data->front();
        }

        const T& front() const {
            check(0, "front() on a empty container");
            return data->front();
        }

        T& operator[](size_type i) {
            check(i, "out of bounds");
            return (*data)[i];
        }

        const T& operator[](size_type i) const {
            check(i, "out of bounds");
            return (*data)[i];
        } 

        //  iterators 
        BlobPtr<T> begin() {
            return BlobPtr<T>(*this, 0);
        }

        BlobPtr<T> end() {
            return BlobPtr<T>(*this, size());
        }

        bool operator<(const Blob &rhs) {
            return *data < *(rhs.data);
        }

    private :
        // container member
        std::shared_ptr<std::vector<T>> data;

        // private utility to check out of bounds
        void check(size_type i, const std::string &msg) const {
            if (i >= data->size()) {
                throw std::runtime_error(msg);
            }
        }
};

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
        return *(lhs.data) == *(rhs.data);
}

#endif 

