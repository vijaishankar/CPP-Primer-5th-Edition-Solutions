/************************************************************************************************************************************************************
 * @file doubly_linked_list.cpp
 * @brief just a simple implementation of doubly linked list.
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>

template <typename T>
struct node {
    T data;
    node * next = nullptr;
    node * previous = nullptr;
    static size_t size;
};

template <typename T>
size_t node<T>::size = 0;

template <typename T>
void print(const node<T> *current) {
    while(current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void insert(node<T> *current, T const &val, size_t pos) {
    if(pos >= current->size) {
        std::cout << "out of bounds" << std::endl;
        return;
    }

    for(size_t i = 0; i < pos; ++i) {
        current = current->next;
    }

    auto *p = new node<T>({val});
    p->previous = current;
    p->next = current->next;
    current->next = p;
    ++current->size;
}

template <typename T>
void remove(node<T> *current, size_t pos) {
    if(pos >= current->size) {
        std::cout << "out of bounds" << std::endl;
        return;
    }

    for(size_t i = 0; i < pos; ++i) {
        current = current->next;
    }

    auto *p = current;
    current->next->previous = current->previous;
    current->previous->next = current->next;
    --current->size;
    delete p;
}

template <typename T>
void reverse_print(const node<T> *current) {
    const node<T> *last = current;
    while(current != nullptr) {
        last = current;
        current = current->next;
    }

    while(last != nullptr) {
        std::cout << last->data << " ";
        last = last->previous;
    }
    
}

/*
int main() {
    node<std::string> *first = new node<std::string>({"hello world"});
    ++first->size;
    
    node<std::string> *current = first;
    for(size_t i = 0; i != 10; i++) {
        auto *p = new node<std::string>({std::to_string(i)});
        p->previous = current;
        current->next = p;
        current = current->next;
        ++current->size;
    }

    print(first);
    insert(first, std::string("middle"), 11);
    print(first);
    remove(first, 7);
    print(first);
    std::cout << "size of list : " << first->size << std::endl;

    reverse_print(first);
    return 0;
}
*/