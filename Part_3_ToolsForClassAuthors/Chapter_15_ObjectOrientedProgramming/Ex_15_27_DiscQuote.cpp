/************************************************************************************************************************************************************
 * @file Ex_15_27.cpp
 * @brief Exercise 15.27: Redefine your Bulk_quote class to inherit its constructors.
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

// base class
class Quote {
public:     //  every one can access the members
    Quote() {
        std::cout << "Quote() : invoked" << std::endl;
    }

    Quote(const std::string& book_no_, double price_)
        : book_no(book_no_), price(price_)
    { std::cout << "Quote(const std::string& book_no_, double price_) : invoked" << std::endl; }

    Quote(const Quote &source) : book_no(source.book_no), price(source.price) {
        std::cout << "Quote(const Quote &source) : invoked" << std::endl;
    }

    Quote(Quote &&rhs) : book_no(std::move(rhs.book_no)), price(std::move(rhs.price)) {
        std::cout << "Quote(const Quote &source) : invoked" << std::endl;
    }

    Quote & operator=(const Quote &rhs) {
        book_no = rhs.book_no;
        price = rhs.price;
        std::cout << "Quote & operator=(const Quote &rhs) : invoked" << std::endl;
        
        return *this;
    }

    Quote operator=(Quote &&rhs){
        book_no = std::move(rhs.book_no);
        price = std::move(rhs.price);
        std::cout << "Quote operator=(Quote &&rhs) : invoked" << std::endl;

        return *this;
    }

    virtual double net_price(size_t count) const {   //  derived classes can override the definition 
        return price * count;
    }

    const std::string& isbn() const {   //   derived classes cannot override these non-virtual functions, they just inherit these
        return book_no;
    }

    virtual void debug() const {
        std::cout << book_no << " " << price << " ";
    }

    virtual ~Quote() {  // base class destructor should be declared as virtual
        std::cout << "~Quote() : invoked" << std::endl;
    } 

private:   //  derived class don't have access to private members like users of the class     
    std::string book_no;    

protected:  //  derived class can access protected members but not the users
    double price;
};

void print_total(const Quote &item, size_t count){
    std::cout << "ISBN : " << item.isbn() << "\n" << 
              "net price : " << item.net_price(count) << std::endl;
}

//  abstract base class
class Disc_quote : public Quote {
public :    
    using Quote::Quote;

    Disc_quote(const std::string &book_no_, double price_, double disc_, size_t qty_) 
        : Quote(book_no_, price_), qty(qty_), disc(disc_) {
            std::cout << "Disc_quote(const std::string &book_no_, double price_, double disc_, size_t qty_) " << std::endl;
    }

    Disc_quote(const Disc_quote &rhs) : Quote(rhs), qty(rhs.qty), disc(rhs.disc) {
        std::cout << "Disc_quote(const Disc_quote &rhs) : Quote(rhs), qty(rhs.qty), disc(rhs.disc) : invoked" << std::endl;
    }

    Disc_quote(Disc_quote &&rhs) : Quote(std::move(rhs)), qty(std::move(rhs.qty)), disc(std::move(rhs.disc)) {
        std::cout << "Disc_quote(Disc_quote &&rhs) : invoked" << std::endl;
    }

    Disc_quote & operator=(const Disc_quote &rhs){
        Quote::operator=(rhs);
        qty = rhs.qty;
        disc = rhs.disc;
        std::cout << "Disc_quote & operator=(const Disc_quote &rhs) : invoked" << std::endl;

        return *this;
    }

    Disc_quote & operator=(Disc_quote &&rhs){
        Quote::operator=(std::move(rhs));
        qty = std::move(rhs.qty);
        disc = std::move(rhs.disc);
        std::cout << "Disc_quote operator=(Disc_quote &&rhs) : invoked" << std::endl;
        return *this;
    }

    double net_price(size_t count) const override = 0;
    void debug() const override {
        Quote::debug();
        std::cout << qty << " " << disc << std::endl;
    }

    ~Disc_quote(){
        std::cout << "~Disc_quote() : invoked" << std::endl;
    }

protected :
    size_t qty;
    double disc;
};

// derived class, derives from quote
class Bulk_quote : public Disc_quote {   //  The interface of base class becomes part of derived class
public :
    using Disc_quote::Disc_quote;

    //  virtual function overriden 
    double net_price(size_t count) const override {
        if (count >= qty) {
            return count * (1 - disc) * price;
        } else {
            return count * price;
        }
    }

    void debug() const override {
        Disc_quote::debug();
    }

};

// derived class, derives from Quote
class LimitedQuote : public Disc_quote {     //  interface of Quote is part of the interface of LimitedQuote
public :    
    using Disc_quote::Disc_quote;

    double net_price(size_t count) const override {
        if(count <= qty){
            return count * (1 - disc) * price;
        } else {
            return qty * (1 - disc) * price + (count - qty) * price;
        }
    }

    void debug() const override {
        Disc_quote::debug();
    }

    ~LimitedQuote(){
        std::cout << "~LimitedQuote() : invoked" << std::endl;
    }
};

