/************************************************************************************************************************************************************
 * @file Ex_14_7.cpp
 * @brief Exercise 14.7: Define an output operator for you String class you wrote for the exercises in § 13.5 (p. 531).
 * @date 2024-01-29
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
#include <cstring>
#include <vector>

class String {
    friend std::ostream & operator<<(std::ostream &os, const String &str);
    public :
        String() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        String(const char *p);
        String(const String &source);
        String(String &&source) noexcept;
        String & operator=(String rhs);
        String & operator=(String &&rhs);
        char * begin() const;
        char * end() const;
        ~String(){ free(); }
        size_t size();
        void reserve(const size_t sz);
        size_t capacity();
        void push_back(const char &ch);
    private :
        void swap(String &lhs, String &rhs);
        void check_n_alloc();
        void realloc(const size_t sz = 0);
        void free();
        std::pair<char *, char *> alloc_n_copy(const char *b, const char *e);
        char * elements;
        char * first_free;
        char * cap;
        std::allocator<char> alloc;
};

std::ostream & operator<<(std::ostream &os, const String &str){
    auto iter = str.begin();
    while(iter != str.end()){
        os << *iter++;
    }

    return os;
}

String::String(const char *p){
    std::cout << "String(const char *p) : " << std::endl;
    std::cout << "sizeof(p) " << strlen(p) << std::endl;
    auto data = alloc_n_copy(p, p + strlen(p));
    elements = data.first;
    first_free = cap = data.second;
}

String::String(const String &source){
    std::cout << "String(const String &source) :" << std::endl;
    auto data = alloc_n_copy(source.begin(), source.end());
    elements = data.first;
    first_free = cap = data.second;
}

String::String(String &&source) noexcept : elements(source.elements), first_free(source.first_free), cap(source.cap){
    std::cout << "String::String(String &&source) noexcept : " << std::endl;
    source.elements = source.first_free = source.cap = nullptr;
}


char * String::begin() const {
    return elements;
}

char * String::end() const {
    return first_free;
}

String & String::operator=(String rhs){
    std::cout << "operator=(String rhs) : " << std::endl;
    swap(*this, rhs);
    return *this;
}

String & String::operator=(String &&rhs){
    std::cout << "String::operator=(String &&rhs) : " << std::endl;
    if(this != &rhs){
        swap(*this, rhs);
    }
    return *this;
}

void String::swap(String &lhs, String &rhs){
   using std::swap;
   swap(lhs.elements, rhs.elements);
   swap(lhs.first_free, rhs.first_free);
   swap(lhs.cap, rhs.cap);
}

void String::check_n_alloc(){
    if(first_free == cap){
        realloc();
    }
}

size_t String::size(){
    return first_free - elements;
}

void String::reserve(const size_t sz){
    realloc(sz);
}

size_t String::capacity(){
    return cap - elements;
}

void String::realloc(const size_t sz){
    size_t new_capacity;
    if(!sz){
        new_capacity = size() ? 2 * size() : 1;
    }else if( sz && sz > capacity()){
        new_capacity = sz;
    }else {
        return ;
    }

    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(first_free), new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

void String::free(){
    while(first_free != elements){
        std::destroy_at(--first_free);
    }
    alloc.deallocate(elements, cap - elements);
    elements = first_free = cap = nullptr;
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e){
    auto new_elements = alloc.allocate(e - b);
    auto new_first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, new_first_free};
}

void String::push_back(const char &ch){
    check_n_alloc();
    std::construct_at(first_free++, ch);
}

int main(){
    String str("hello world");
    std::cout << str << std::endl;

    return 0;
}