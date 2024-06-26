/************************************************************************************************************************************************************
 * @file Ex_15_30.cpp
 * @brief Exercise 15.30: Write your own version of the Basket class and use it to compute prices for the same 
 * transactions as you used in the previous exercises.
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * Basket class :  class that stores sales 
 *      addItem  :  adds pointer to Quote and types derived from it in a multiset
 *      total_reciept : calculates the sum of entire baseket, but sum of similar items are show individualy
 *      as shared_ptrs don't have < operator, we supply a compareIsbn function to multiset as it requires one to store
 * 
 * 
 * Quote and derived classes should have virtual clone() function to allocate dynamically a copy of itself
 * 
 * 
 *************************************************************************************************************************************************************/

#include <set>
#include <memory>
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

    virtual Quote * clone() const & {
        return new Quote(*this);
    }

    virtual Quote * clone() && {
        return new Quote(std::move(*this));
    }

private:   //  derived class don't have access to private members like users of the class     
    std::string book_no;    

protected:  //  derived class can access protected members but not the users
    double price;
};

double print_total(const Quote &item, size_t count){
    auto res = item.net_price(count);
    std::cout << "ISBN : " << item.isbn() << "\n" << 
              "net price : " << res << std::endl;

    return res;
}

//  abstract base class
class Disc_quote : public Quote {
public :    
    Disc_quote() {
        std::cout << "Disc_quote() : invoked" << std::endl;
    }

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

    Bulk_quote * clone() const & override {
        return new Bulk_quote(*this);
    }

    Bulk_quote * clone() && override {
        return new Bulk_quote(std::move(*this));
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

    LimitedQuote * clone() const & override  {
        return new LimitedQuote(*this);
    } 

    LimitedQuote * clone() && override {
        return new LimitedQuote(std::move(*this));
    }
};

/************************************************************************************************************************************************************
 * Basket class :  class that stores sales 
 *      addItem  :  adds pointer to Quote and types derived from it in a multiset
 *      total_reciept : calculates the sum of entire baseket, but sum of similar items are show individualy
 *      as shared_ptrs don't have < operator, we supply a compareIsbn function to multiset as it requires one to store
 * 
 *************************************************************************************************************************************************************/
class Basket {
    public :
        //  adds item to the container
        void addItem(const Quote &sale) {
            cart.insert(std::shared_ptr<Quote>(sale.clone()));     //  clone() is a virtual function when called on a type, it allocates memory and copies the item's value and returns it
        }

        void addItem(Quote &&sale) {
            cart.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
        }

        //  calculates the total sum of the container
        double totalSale() {
            double sum = 0;
            for( auto iter = cart.begin(); iter != cart.end(); iter = cart.upper_bound(*iter)){
                auto count = cart.count(*iter);
                sum += print_total(**iter, count);
                
            }

            return sum;
        }

    private :
        //  comparison function for multiset
        static bool compareIsbn(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs){
            return lhs->isbn() < rhs->isbn();
        }

        //  container of type multiset which stores pointers to items
        std::multiset<std::shared_ptr<Quote>, decltype(compareIsbn) *> cart{compareIsbn};
};

int main(){
    Quote q1, q2("c++ primer", 56);
    Bulk_quote bq1, bq2("c++ primer", 45, 0.3, 2);
    LimitedQuote lq1, lq2("c++ primer", 56, 0.2, 1);
    Basket cart;
    cart.addItem(q1);
    cart.addItem(q2);
    cart.addItem(bq1);
    cart.addItem(bq2);
    cart.addItem(lq1);
    cart.addItem(lq2);

    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);

    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);
    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);
    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);
    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);
    cart.addItem(q2);
    cart.addItem(bq2);
    cart.addItem(lq2);
     
    std::cout << "total sale : " << cart.totalSale() << std::endl;

    return 0;
}