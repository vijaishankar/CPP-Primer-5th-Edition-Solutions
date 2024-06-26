/************************************************************************************************************************************************************
 * @file Ex_7_32.cpp
 * @brief Exercise 7.32: Define your own versions of Screen and Window_mgr in which clear is a member of Window_mgr and a 
 *        friend of Screen.
 * @date 2023-12-21
 *   
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Screen;           //  forward declaration of Screen class 

//  definition of WindowManager class follows
class WindowManager{
    public :
        typedef std::vector<Screen>::size_type screenIndex;

        // clear(i) clears the contents of the screen at specified index if present or else informs screen is not present
        void clear(screenIndex i);

        // add(Screen) inserts a Screen obj in windows, parameter is a reference as variable cannot be created for incomplete type
        void add(Screen &s){
            windows.push_back(s);
        }

        //  get(i) returns Screen object at specified index if present or returns last object
        Screen & get(screenIndex i){
            if(i < windows.size()){
                return windows[i];
            }else{
                return windows[windows.size() - 1];
            }
        }
    private : 
        std::vector<Screen> windows;    // Screen obj cannot be defined here as Screen definition is not seen at this point
};

//  definition of Screen follows
class Screen{
    public : 
        typedef std::vector<Screen>::size_type screenIndex;
        typedef std::string::size_type pos;   // to hide type of contents
        friend void WindowManager::clear(screenIndex);  // clear can access Screen's member functions

        Screen() = default;     //  default constructor 

        // takes height and width of screen and initilises the contents with ' '
        Screen(const pos h_p, const pos w_p) : height(h_p), width(w_p), contents(std::string(h_p * w_p, '*')) { std::cout << contents.size() << std::endl;}

        // takes height, width, and character to intialises contents
        Screen(const pos h_p, const pos w_p, const char ch) : height(h_p), width(w_p), contents(std::string(h_p * w_p, ch)) { std::cout << contents.size() << std::endl;}

        //  get() returns the character at current cursor position if contents is not empty or else returns -1
        char get() const {
            return (contents.empty()) ? -1 : contents[cursor] ;
        }

        //  get(r,c) returns the character at the position specified by row and coloumn, if position doesn't exist it returns -1
        char get(const pos r, const pos c) const ;

        //  moves the cursor to a position specified by row and coloumn, if position doesn't exist returns character at the end of screen
        Screen move(const pos r, const pos c);

        Screen set(const char ch);    //  writes a character at current cursor position

        Screen set(const pos r, const pos c, char ch);  //  writes a character at specified position

        
        // const member function to call do_display() from const obj, as 'this' is pointer to const, *this is reference to const
        const Screen display(std::ostream &os) const {
            do_display(os);
            return *this;
        }

        // non-const member function to call do_display()
        Screen display(std::ostream &os){
            do_display(os);
            return *this;
        }

        //  it prints the contents of the screen, declared as const for const display() to call 
        void do_display(std::ostream &os) const {
            os << contents;
        }

        /*  reason for overloading display() with const :
            to facilitate screenobj.move(1,2).display(std::cout).set('%') and similar chain operations
            we are returning Screen &
            for const Screen obj to call display() it needs to be a const member function
            but if it is const then it will return ref to const
            so for non-const obj we won't be able to chain display() with other mem_func
            so there should be two display()
                one returning non-const ref
                another one returning const ref as it is const mem-function
            */
        /*  reason for seperate function do_display() to print : 
            1. not to repeat common code for 2 or more mem_func
            2. as the class Screen evolves the displaying the contents may get complicated, so having the code at one place
                is easy to update
            3. If we add debugging code to displaying contents, then it is easy if the code is at one place
            4. there is no over-head in calling do_display() as it is defined inside the class, it is inline
             */   
    private :
        pos height = 0;
        pos width = 0;
        pos cursor = 0;        // cursor is the index of the contents, so starts from zero  
        std::string contents;  // if height = 4, width = 5, then contents will be of size = 4 * 5
};

//  validity of the position is checked based on, height implifies rows, so height >= r or if height is greater than specified coloumn should be lesser than or equal to width
inline char Screen::get(const pos r, const pos c) const {
    int row = r * width - 1 ;
    if(contents.empty()){
        return -1;
    }else if( contents.size() <= row + c){
        return contents.back();
    }else{
        return contents[row + c] ;         //  -1 is to account that index starts from zero
    }
}

// Screen::move(r,c) definiton
inline Screen Screen::move(const pos r, const pos c) {
    int row = r * width - 1;
    if(!contents.empty()){
        if( contents.size() <= row + c){
            cursor = contents.size() - 1;     
        }else{
            cursor = row + c;
        }
    }    
    return *this;
}

// Screen::set(ch) definition
inline Screen Screen::set(const char ch){
    if(contents.empty()){
        contents.push_back(ch);    
    }else{
        contents[cursor] = ch;
    }

    return *this;
}

//  Screen::set(r,c,ch) definition
inline Screen Screen::set(const pos r, const pos c, char ch){
    int row = r * width - 1;
    if(contents.empty()) {
        contents.push_back(ch);
    }else if(contents.size() <= row + c) {    
        contents[contents.size() -1] = ch;
    }else{
        contents[row + c] = ch;
    }

    return *this;
}

//  WindowManager::clear is defined after the defintion of Screen class as we have to access s.contents
void WindowManager::clear(screenIndex i){
    if(i >= windows.size() ){
        std::cerr << "no screen present with specified id" << std::endl;
    }else{
        Screen &s = windows[i];
        s.contents = std::string(s.height * s.width, ' ');
    }
}

int main(){
    WindowManager windows;
    Screen s1(4,5,'$');
    windows.add(s1);        
    Screen s2(6,5);
    windows.add(s2);

    windows.get(3).display(std::cout);
    windows.clear(1);

    std::cout << std::endl;
    windows.get(1).display(std::cout);

    return 0;
}