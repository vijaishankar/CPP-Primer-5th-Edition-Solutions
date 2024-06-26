/************************************************************************************************************************************************************
 * @file Ex_13_10.cpp
 * @brief Exercise 13.10: What happens when a StrBlob object is destroyed? What about a StrBlobPtr?
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

// As StrBlob contains a shared_ptr to the data, when its object is destroyed the destructor of the shared_ptr is run, 
// the use_count is decreased by 1, when the use_count becomes 0, the data is destroyed by running the vector's destructor

// As for StrBlobPtr, as it contains a weak_ptr, when it is destroyed, destructor of the object calls the destructor of the 
// weak_ptr which in turns destroys the weak_ptr, but it won't affect shared_ptr

//  libraries needed
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
#include <exception>

// StrBlob, all objects share the same underlying data, vector of strings
class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
    public :
        // type alias for size
        typedef std::vector<std::string>::size_type size_type;

        // constructors
        StrBlob();
        StrBlob(const std::initializer_list<std::string> &il);

        // size operations
        size_type size() const;
        bool empty() const;

        // access operations
        StrBlobPtr begin();
        StrBlobPtr end();
        std::string& front();
        std::string& back();
        const std::string & front() const;
        const std::string & back() const;
        void push_back(const std::string &word);
        void pop_back();
        size_t count(){
            return data.use_count();
        }

    private :
        // shared_ptr to point to container
        std::shared_ptr<std::vector<std::string>> data;
        void check(size_type i, const std::string &msg) const ;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(const std::initializer_list<std::string> &il) : data(std::make_shared<std::vector<std::string>>(il)) {}

StrBlob::size_type StrBlob::size() const {
    return data->size();
}

bool StrBlob::empty() const {
    return data->empty();
}

std::string & StrBlob::front(){
    check(0,"container is empty");
    return data->front();
}

std::string & StrBlob::back(){
    check(0,"container is empty");
    return data->back();
}

const std::string & StrBlob::front() const{
    check(0,"container is empty");
    return data->front();
} 

const std::string & StrBlob::back() const{
    check(0, "container is empty");
    return data->back();
}

void StrBlob::push_back(const std::string &word) {
    data->push_back(word);
}

void StrBlob::pop_back() {
    check(0, "container is empty");
    data->pop_back();
}

void StrBlob::check(size_type i, const std::string &msg) const {
    if( i >= data->size()){
        throw std::runtime_error(msg);
    }
}

// ptr class to StrBlob class, this class creates iterators to iterate through the StrBlob container
class StrBlobPtr{
    public :
        StrBlobPtr() : curr(0) {}
        StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
        std::string & deref() const;
        StrBlobPtr & incr();
        
    private : 
        std::weak_ptr<std::vector<std::string>> wptr;  // will point to data member, we use weak_ptr to make sure vector is not asscessed if no shared_ptr exists
        size_t curr;
        std::shared_ptr<std::vector<std::string>> check(size_t curr, const std::string &msg) const ; 
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t curr, const std::string &msg) const {
    auto sp = wptr.lock();
    if(!sp){
        throw std::runtime_error("unbound StrBlobPtr");
    }else if(curr >= sp->size()){
        throw std::out_of_range(msg);
    }
    
    return sp;
}

std::string & StrBlobPtr::deref() const{
    auto sp = check(curr, "out of bounds");
    return (*sp)[curr];
}

StrBlobPtr & StrBlobPtr::incr(){
    check(curr, "cannot be incremented");
    ++curr;
    return *this;
}


StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    return StrBlobPtr(*this, data->size());
}

int main(){
    StrBlob b1({"hello","world"});
    {
        StrBlob b2(b1);
        std::cout << "b1.count : " << b1.count() << " " << "b2.count : " << b2.count() << std::endl; 
    }    
    std::cout << "after b2 is destroyed" << std::endl;

    std::cout << "b1.count : " << b1.count() << std::endl;    
    StrBlobPtr iter1 = b1.begin();
    {
        StrBlobPtr iter2 = iter1;
        std::cout << "iter2 = iter1" << std::endl;
        std::cout << "*iter2 : " << iter2.deref() << std::endl;
        std::cout << "b1.count : " << b1.count() << std::endl;
    }
    std::cout << "after iter2 is destroyed" << std::endl;
    std::cout << "b1.count : " << b1.count() << std::endl;    
    return 0;
}

