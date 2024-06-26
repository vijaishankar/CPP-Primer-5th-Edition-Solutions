/************************************************************************************************************************************************************
 * @file Ex_13_34.cpp
 * @brief Exercise 13.34: Write the Message class as described in this section.
 * @date 2024-01-24
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

class Folder;
// Message objects will contain msg and a set of folders which contains the message
class Message{
    friend void swap(Message &lhs, Message &rhs);
    public :
        // default constructor and constructor that takes a string
        Message(const std::string &msg = "") : contents(msg) {}        
         // copy_constructor
        Message(const Message &source) : contents(source.contents), folders(source.folders) {
            addToFolders(source);
        }    
        Message & operator=(Message &m);    // copy_assignment operator

        ~Message(){     // destructor
            removeFromFolders();
        }

        void save(Folder &);   //  adds the folder to its list and makes the folder to add this 
        void remove(Folder &); //  removes the folder from its list and makes the folder to remove this 
        void print();  // prints the data      
        const std::string & get_msg(){
            return contents;
        }   
    private :
        // private utility functions
        void removeFromFolders();
        void addToFolders(const Message &source);

        // data members
        std::string contents;
        std::set<Folder *> folders;
};

//  Folder class contains set of Messages and members to add and remove a Message 
class Folder{
    public :
        Folder(const std::string &str) : name(str) {}
        void addMsg(Message &m); 
        void rmvMsg(Message &m);
        void print();
        std::string get_name(){ return name ;}
    private :
        std::string name;
        std::set<Message *> messages;
};

//  adds a folder to the folders list and makes the folder to add this in to its set of Messages
void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(*this);
}

// removes a folder from the folders list and makes the folder to remove this from its set of Messages
void Message::remove(Folder &f){
    folders.erase(&f);
    f.rmvMsg(*this);
}

// private utility function to remove this Message from all the Folders that contains it
void Message::removeFromFolders(){
    for(auto f : folders){
        f->rmvMsg(*this);
    }   
}

// private utility function to add this Message to all the Folders the source contains 
void Message::addToFolders(const Message &source){
    for(auto f : source.folders){
        f->addMsg(*this);
    }

}

// copy_assignment operator, copies the contents and Folers list
Message & Message::operator=(Message &rhs){
    removeFromFolders();
    contents = rhs.contents;
    folders = rhs.folders;
    addToFolders(rhs);

    return *this;
}

//  adds a Message to the list of Messages the folder contains
void Folder::addMsg(Message &m){
    messages.insert(&m);
}

//  removes a Message from the list of Messages the folder contains
void Folder::rmvMsg(Message &m){
    messages.erase(&m);
}

void Message::print(){
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "msg : " << contents << std::endl;
    std::cout << "folders : ";
    for(auto f : folders){
        std::cout << f->get_name() << " || ";

    }
    std::cout << std::endl;
}

void Folder::print(){
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "name : " << name << std::endl;
    std::cout << "msgs : " << std::endl;
    for(auto m : messages){
        std::cout << m->get_msg() << std::endl;
    } 
}

void swap(Message &lhs, Message &rhs){
    using std::swap;
    lhs.removeFromFolders();
    rhs.removeFromFolders();
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);
    lhs.addToFolders(lhs);
    rhs.addToFolders(rhs);
}

int main(){
    Folder f1("all"), f2("important"), f3("spam");
    Message m1("msg1"), m2("msg2"), m3("msg3");
    m1.save(f1);
    m2.save(f2);
    m3.save(f3);
    m1.save(f2);
    m1.save(f3);
    m1.remove(f2);
    m1.print();
    m2.print();
    m3.print();
    f1.print();
    f2.print();
    f3.print();
    std::cout << "=====================================================";
    swap(m1, m2);
    m1.print();
    m2.print();
    m3.print();
    f1.print();
    f2.print();
    f3.print();
    return 0;
}




