/*  Exercise 7.29: Revise your Screen class so that move, set, and display functions return Screen and check your prediction
 *  from the previous exercise. */

#include <iostream>
#include <string>
//  definition of class
class Screen{
    public : 
        typedef std::string::size_type pos;   // to hide type of contents

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

inline Screen Screen::set(const char ch){
    if(contents.empty()){
        contents.push_back(ch);    
    }else{
        contents[cursor] = ch;
    }

    return *this;
}

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

int main(){
    Screen s1;
    std::cout << "s2 is created with size : ";
    Screen s2(4,5);
    std::cout << std::endl << "size of s3 : ";
    Screen s3(2,3,'#');
    std::cout << s1.get() << std::endl;
    std::cout << s2.get() << std::endl;
    std::cout << s3.get() << std::endl;
    std::cout << s1.get(4,5) << std::endl;
    std::cout << s2.get(4,5) << std::endl;
    std::cout << s3.get(2,4) << std::endl;

    s1.move(2,5);
    s2.move(4,5);
    s3.move(2,1);
    std::cout << s1.get() << std::endl;
    std::cout << s2.get() << std::endl;
    std::cout << s3.get() << std::endl;

    s2.display(std::cout);    
    std::cout << std::endl;
    s2.set('$').display(std::cout);
    std::cout << std::endl;

    s3.display(std::cout); 
    std::cout << std::endl;
    s3.set(2,4,'$').display(std::cout);
    std::cout << std::endl;

    s2.display(std::cout); 
    std::cout << std::endl;
    s2.set(4,5,'@').display(std::cout);
    std::cout << std::endl;

    s3.display(std::cout); 
    std::cout << std::endl;
    s3.set('!').display(std::cout);
    std::cout << std::endl;

    const Screen s4(6,6,'~');
    s4.display(std::cout);
    std::cout << std::endl;
    std::cout << s4.get() << " " << s4.get(6,6) << std::endl;

    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
    return 0; 
}

/*  because of returning a copy of the object, further operations are carried out in the new object not the original
 *
 *  output of myScreen :
 *
 *  25
 *  XXXXXXXXXXXXXXXXXXX#XXXXX
 *  XXXXXXXXXXXXXXXXXXXXXXXXX
 * 
 *  2nd line of output is the temp object
 *  3rd line of output is the myscreen object
 *  thought we have chained the operations, the set() function was called on temp object as move returned a copy of myscreen 
 * */
             