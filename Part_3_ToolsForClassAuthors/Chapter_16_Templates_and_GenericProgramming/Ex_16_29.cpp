/************************************************************************************************************************************************************
 * @file Ex_16_29.cpp
 * @brief Exercise 16.29: Revise your Blob class to use your version of shared_ptr rather than the library version.
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <memory>
#include <initializer_list>

#include "Ex_16_28_SmartPointer.cpp"

template <typename T> 
class weak_ptr {
    public :
        weak_ptr() : s_ptr(nullptr) {}
        weak_ptr(shared_ptr<T> &p) : s_ptr(&p) {}
        weak_ptr(shared_ptr<T> &&p) = delete;
        shared_ptr<T> lock(){
            return *(s_ptr->count) ? *s_ptr : nullptr;
        }
        ~weak_ptr() {
            s_ptr = nullptr;
        } 
    private :
        shared_ptr<T> *s_ptr;
};

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
        Blob(const std::initializer_list<T> &il) : data(new std::vector<T>(il)) {
            data.setDeleter(DebugDelete());
        }

        template <typename It> 
        Blob(It b, It e) : data(new std::vector<T>(b,e)) {
            data.setDeleter(DebugDelete());
        }

        // size related members
        size_type size() {
            return data->size();
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
        shared_ptr<std::vector<T>> data;

        // private utility to check out of bounds
        void check(size_type i, const std::string &msg) {
            if (i >= data->size()) {
                throw std::runtime_error(msg);
            }
        }
};

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
        return *(lhs.data) == *(rhs.data);
}

template<typename> class BlobPtr;
template <typename T> 
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template <typename T>
class BlobPtr {
    friend bool operator== ( BlobPtr &lhs, BlobPtr &rhs) {
        return lhs.w_ptr.lock() == rhs.w_ptr.lock() && lhs.curr == rhs.curr;
    }

    friend bool operator!= ( BlobPtr &lhs, BlobPtr &rhs) {
        return !(lhs == rhs);
    }
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
        weak_ptr<std::vector<T>> w_ptr;
        size_type curr;

        //  private utility
        shared_ptr<std::vector<T>> check(size_type i, const std::string &msg) {
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

int main() {
    Blob<int> ib{2,3,4,6,8,10};
    for(size_t i = 0; i < ib.size(); ++i) {
        std::cout << ib[i] << " ";
    }

    std::cout << std::endl;

    auto iter = ib.begin();
    auto end = ib.end();

    for( auto iter = ib.begin(); iter != end; ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}