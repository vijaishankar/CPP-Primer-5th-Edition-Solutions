/************************************************************************************************************************************************************
 * @file Ex_16_58.cpp
 * @brief Exercise 16.58: Write the emplace_back function for your StrVec class and for the Vec class that you wrote
 * for the exercises in § 16.1.2 (p. 668).
 * @date 2024-02-17
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

//************************************************StrVec class************************************************************
/*
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>
#include <initializer_list>

class StrVec{
    friend void swap(StrVec &lhs, StrVec &rhs);
    friend bool operator<(const StrVec &lhs, const StrVec &rhs);
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);
    friend bool operator!=(const StrVec &lhs, const StrVec &rhs);
    public :
        StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        StrVec(const StrVec &);
        StrVec(StrVec &&) noexcept;
        StrVec & operator=(const StrVec &rhs);
        StrVec & operator=(StrVec &&rhs) noexcept;
        StrVec(const std::initializer_list<std::string> &il);
        size_t size() const ;
        size_t capacity() const;
        void reserve(const size_t sz);
        void push_back(const std::string &);
        template <typename... Args>
        void emplace_back(Args&&... args);
        const std::string *begin() const ;
        const std::string *end() const ;
        StrVec & operator=(const std::initializer_list<std::string> &il);
        ~StrVec(){ free(); }

    private :
        std::string *elements;
        std::string *first_free;
        std::string *cap;

        std::allocator<std::string> alloc;
        void realloc(const size_t sz = 0);
        void check_n_alloc();
        std::pair<std::string *, std::string *> alloc_n_copy(const std::string *b, const std::string *e);
        void free();
};

template <typename... Args>
void StrVec::emplace_back(Args&&... args) {
    check_n_alloc();
    std::construct_at(first_free++, std::forward<Args>(args)...);  //  expands in to std::forward<Ti>(ti)  
}

StrVec & StrVec::operator=(const std::initializer_list<std::string> &il){
    StrVec temp(il);
    swap(*this, temp);
    return *this; 
}
StrVec::StrVec(const StrVec &source){
    std::cout << "StrVec::StrVec(const StrVec &source)" << std::endl;
    auto new_data = alloc_n_copy(source.begin(), source.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec::StrVec(StrVec &&source) noexcept : elements(source.elements), first_free(source.first_free), cap(source.cap){
    std::cout << "StrVec::StrVec(StrVec &&source) noexcept : " << std::endl;
    source.elements = source.first_free = source.cap = nullptr;
}


StrVec & StrVec::operator=(const StrVec &rhs){
    std::cout << "StrVec::operator=(const StrVec &rhs) : " << std::endl;
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;

    return *this;
}

void swap(StrVec &lhs, StrVec &rhs){
    std::cout << "void swap(StrVec &lhs, StrVec &rhs) : " << std::endl;
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
    std::cout << "StrVec::operator=(StrVec &&rhs) noexcept : " << std::endl;
    if(this != &rhs){
        swap(*this, rhs);
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }

    return *this;
}


StrVec::StrVec(const std::initializer_list<std::string> &il){
    std::cout << "StrVec::StrVec(const std::initializer_list<std::string> &il) : " << std::endl;
    auto data = alloc_n_copy(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

size_t StrVec::size() const {
    return first_free - elements;
}

size_t StrVec::capacity() const{
    return cap - elements;
}

void StrVec::reserve(const size_t sz) {
    realloc(sz);
}

void StrVec::push_back(const std::string &str){
    check_n_alloc();
    std::construct_at(first_free++, str);
}

const std::string *StrVec::begin() const{
    return elements;
}

const std::string *StrVec::end() const{
    return first_free;
}

void StrVec::realloc(const size_t sz){
    std::cout << "StrVec::realloc(const size_t sz) : " << std::endl;
    size_t new_capacity;
    if (!sz) {
        new_capacity = size() ? 2 * size() : 1;
    } else if (sz && sz > capacity()) {
        new_capacity = sz;
    } else {
        return;
    }
    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(first_free), new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

void StrVec::check_n_alloc(){
    if(first_free == cap)
        realloc();
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e){
    auto new_elements = alloc.allocate(e - b);
    auto first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, first_free};
}

void StrVec::free(){
    if(elements){
        while(first_free != elements){
            std::destroy_at(--first_free);
        }
    }
    alloc.deallocate(elements, cap - elements);
}   
void print(const StrVec &svec){
    if(svec.size() == 0){
        std::cout << "list is empty" << std::endl;
        return;
    }

    std::cout << "====================================================" << std::endl << "##  ";
    for(auto iter = svec.begin(); iter != svec.end(); ++iter){
        std::cout << *iter << " ";
    }
    std::cout << "  ##" << std::endl;
    return;
}

bool operator==(const StrVec &lhs, const StrVec &rhs){
    if(lhs.size() != rhs.size()){
        return 0;
    }

    auto iterlhs = lhs.begin();
    auto iterrhs = rhs.begin();
    while(iterlhs != lhs.end()){
        if(*iterlhs++ != *iterrhs++){
            return 0;
        }
    }
    return 1;
}

bool operator!=(const StrVec &lhs, const StrVec &rhs){
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs){
    auto iterlhs = lhs.begin();
    auto iterrhs = rhs.begin();
    if(lhs.size() == rhs.size()){
        while(iterlhs != lhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 1;
    } else if (lhs.size() < rhs.size()) {
        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        while(iterlhs != lhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 1;
    } else {
        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        while(iterrhs != rhs.end()){
            if(*iterlhs++ > *iterrhs++){
                return 0;
            }
        }
        return 0;
    }
}

int main() {
    StrVec svec{"alpha","beta"};
    svec.emplace_back("gamma");  //  alloc.construct_at(first_free, std::forward<StrVec>(StrVec("gamma"))) , calls move constructor
    svec.emplace_back(10,'H');   //  alloc.construct_at(firsr_free, std::forward<int>(10), std::forward<char>('H'));
    
    for(auto s : svec) {
        std::cout << s << " ";
    }

    return 0;
}
*/
//************************************************************************************************************************

//**********************************************Vec class***************************************************************************

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>
#include <initializer_list>

template <typename T>
class Vec {
    friend inline void swap(Vec &lhs, Vec &rhs) {
        std::cout << "void swap(Vec &lhs, Vec &rhs) : " << std::endl;
        using std::swap;
        swap(lhs.elements, rhs.elements);
        swap(lhs.first_free, rhs.first_free);
        swap(lhs.cap, rhs.cap);
    }

    friend inline bool operator<(const Vec &lhs, const Vec &rhs){
        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        if(lhs.size() == rhs.size()){
            while(iterlhs != lhs.end()){
                if(*iterlhs++ > *iterrhs++){
                    return 0;
                }
            }
        return 1;
        } else if (lhs.size() < rhs.size()) {
            auto iterlhs = lhs.begin();
            auto iterrhs = rhs.begin();
            while(iterlhs != lhs.end()){
                if(*iterlhs++ > *iterrhs++){
                    return 0;
                }
            }
            return 1;
        } else {
            auto iterlhs = lhs.begin();
            auto iterrhs = rhs.begin();
            while(iterrhs != rhs.end()){
                if(*iterlhs++ > *iterrhs++){
                    return 0;
                }
            }
            return 0;
        }
    }

    friend inline bool operator==(const Vec &lhs, const Vec &rhs) {
        if(lhs.size() != rhs.size()){
            return 0;
        }

        auto iterlhs = lhs.begin();
        auto iterrhs = rhs.begin();
        while(iterlhs != lhs.end()){
            if(*iterlhs++ != *iterrhs++){
                return 0;
            }
        }
        return 1;   
    }
    friend inline bool operator!=(const Vec &lhs, const Vec &rhs) {
        return !(lhs == rhs);
    }
    public :
        Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        Vec(const Vec &);
        Vec(Vec &&) noexcept;
        Vec & operator=(const Vec &rhs);
        Vec & operator=(Vec &&rhs) noexcept;
        Vec(const std::initializer_list<T> &il);
        size_t size() const ;
        size_t capacity() const;
        void reserve(const size_t sz);
        void push_back(const T &);
        template <typename... Args>
        void emplace_back(Args&&... args);
        const T *begin() const ;
        const T *end() const ;
        Vec & operator=(const std::initializer_list<T> &il);
        ~Vec(){ free(); }

    private :
        T *elements;
        T *first_free;
        T *cap;

        std::allocator<T> alloc;
        void realloc(const size_t sz = 0);
        void check_n_alloc();
        std::pair<T *, T *> alloc_n_copy(const T *b, const T *e);
        void free();
};

template <typename T>
template <typename... Args>
void Vec<T>::emplace_back(Args&&... args) {
    check_n_alloc();
    std::construct_at(first_free++, std::forward<Args>(args)...);
}

template <typename T>
Vec<T> & Vec<T>::operator=(const std::initializer_list<T> &il){
    Vec temp(il);
    swap(*this, temp);
    return *this; 
}

template <typename T>
Vec<T>::Vec(const Vec &source){
    std::cout << "Vec::Vec(const Vec &source)" << std::endl;
    auto new_data = alloc_n_copy(source.begin(), source.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

template <typename T>
Vec<T>::Vec(Vec &&source) noexcept : elements(source.elements), first_free(source.first_free), cap(source.cap){
    std::cout << "Vec::Vec(Vec &&source) noexcept : " << std::endl;
    source.elements = source.first_free = source.cap = nullptr;
}

template <typename T>
Vec<T> & Vec<T>::operator=(const Vec &rhs){
    std::cout << "Vec::operator=(const Vec &rhs) : " << std::endl;
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;

    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator=(Vec &&rhs) noexcept{
    std::cout << "Vec::operator=(Vec &&rhs) noexcept : " << std::endl;
    if(this != &rhs){
        swap(*this, rhs);
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }

    return *this;
}


template <typename T>
Vec<T>::Vec(const std::initializer_list<T> &il){
    std::cout << "Vec::Vec(const std::initializer_list<std::string> &il) : " << std::endl;
    auto data = alloc_n_copy(il.begin(), il.end());
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
size_t Vec<T>::size() const {
    return first_free - elements;
}

template <typename T>
size_t Vec<T>::capacity() const{
    return cap - elements;
}

template <typename T>
void Vec<T>::reserve(const size_t sz) {
    realloc(sz);
}

template <typename T>
void Vec<T>::push_back(const T &val){
    check_n_alloc();
    std::construct_at(first_free++, val);
}

template <typename T>
const T *Vec<T>::begin() const{
    return elements;
}

template <typename T>
const T *Vec<T>::end() const{
    return first_free;
}

template <typename T>
void Vec<T>::realloc(const size_t sz){
    std::cout << "Vec::realloc(const size_t sz) : " << std::endl;
    size_t new_capacity;
    if (!sz) {
        new_capacity = size() ? 2 * size() : 1;
    } else if (sz && sz > capacity()) {
        new_capacity = sz;
    } else {
        return;
    }
    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(first_free), new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

template <typename T>
void Vec<T>::check_n_alloc(){
    if(first_free == cap)
        realloc();
}

template <typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e){
    auto new_elements = alloc.allocate(e - b);
    auto first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, first_free};
}

template <typename T>
void Vec<T>::free(){
    if(elements){
        while(first_free != elements){
            std::destroy_at(--first_free);
        }
    }
    alloc.deallocate(elements, cap - elements);
}   

int main() {
    

    Vec<std::string> strvec{"alpha", "beta","gamma"};
    strvec.emplace_back("delta");
   
    std::cout << std::endl;

    for(auto val : strvec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}