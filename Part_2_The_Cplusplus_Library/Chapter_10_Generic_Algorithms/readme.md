# Generic Algorithms    
- Independent of container type and element type.
- They don't use container operations, they only use iterators so algorithms depend only on operations defined by iterators

## ALGORITHMS THAT READS
### find(b, e, val) -> iter
    find() takes two iterators and val, where b and e indicates the range of elements to search, val is the value to be searched, and returns the iterator to the first element that matches the val or else returns the second iterator( mostly off-the-end) to indicate the failure
### find_if(b, e, predicate) -> iter
    b,e : iterators indicating range
    predicate : unary predicate to be called
    returns iterator for the first element for which predicate is true

### count(b, e, val) -> int 
    count() takes two iterators and val, where b and e is the range, val is the value to be searched, returns number of occurances the value matches with the elements in the range, or else returns 0.

### accumulate(b, e, init_val) -> decltype(init_val) 
    sums up the elements in the range b and e. init_val is initial value of the sum. 
    type of sum and return type is the type of init_val, so elements should be compatible with init_val

### equal(b1, e1, b2) -> bool
    compares the elements of two containers of any type untill the elements are comparable.
    b1,e1 indicates the range1 and b2 indicates the first element in the second range, returns true if each element is equal
    or else false
    assumes the second range is large enough as the first range, or out of bounds error

### for_each(b, e, callable_object)
    b,e : range of elements 
    for_each() calls the callable_object on each element in the range

## ALGORITHMS THAT WRITES
### fill(b, e, val)
    b,e - range
    val - value
    fill(), takes two iterators indicating the range and the value, which it assigns to each and every element in the range

### fill_n(dest, n, val)
    dest - iterator indicating destination which to be writen
    fill_n() takes a single iterator indicating the destination sequence, where n elements in the sequence will be assigned 
    with a value indicated by val.
    assumes there are atleast n elements in the dest sequence, if not undefined

### back_inserter(container_ref)
    back_inserter(), takes a reference to a container and returns a insert iterator
    insert iterator is one which adds elements to the container through container operations
    normaly algorithms uses iter - it writes to existing element, but when we assign a val to insert iterator, it is added as new element in the container by calling push_back().
    ex:- 
        vector<int> vec;  // empty vector
        auto beg = vec.begin();
        *beg = 23 // undefined as vector is empty
        auto it = back_inserter(vec);
        *it = 23 // ok : calls push_back(23)

### copy(b1, e1, dest)
    b1 and e1 indicates the first sequence from which elements need to be copied
    dest iterator indicates the sequence to which copied elements need to be writen
    returns destination iterator one past the last element writen to dest

### replace(b, e, old_val, new_val)
    b,e : range of elements in the sequence
    replace(), takes two iterators indicating the range of elements, each element in the range is matched with old_val, if it
    is true, then it will be replaced with new_val

### replace_copy(b1, e1, dest, old_val, new_val)
    copy version of replace, instead of replacing the matched elements in the sequence, it copies the original sequence and 
    writes to a new sequence with old_val replaced with new_val

## ALGORITHMS THAT REARRANGES CONTAINERS
### sort(b, e) or sort(b,e, predicate)
    sorts the elements in the sequence using element's < operator
    predicate : 
        unary predicate : function that takes single parameter and returns bool 
        binary predicate : function that takes two parameter and returns bool
    a predicate is used in the place of default '<', '==' operators defined by the element
    ex:- sort(b,e) : sorts the sequence in the dictionary order
         sort(b,e, predicate) , where we can write a predicate to compare the size of the elements, so sorts the sequence based on length
    
### stable_sort(b, e, predicate)  or  stable_sort(b, e)

    b,e : the range of elements in the sequence0
    stable_sort() sorts the elements preserving the original order of the equal elements

    ex :- list of words in alphabetical order
           ### fox jumps over quick red slow the turtle 

          order of words after stable sort with predicate that compares length
           ### fox red the over slow jumps quick turtle  
          the list is sorted based on the length of words but alphabetical order is preserved for the words with equal length

### partition(b, e, predicate)
    b,e : indicates the range of elements
    rearranges the list in such a way that the elements for which predicate is true appears first and the rest in the back
    returns an iterator to the element next to the last element for which predicate is true

### stable_partition(b, e, predicate)
    partitions the list preserving the original order




# LAMBDA    
## [CAPTURE_LIST](PARAM..)-> RETURN_TYPE {BODY}
    - LAMBDA's are callable objects, a callable object is a expression to which a call,() operator can be applied.
    - lamda's can use a variable defined in the enclosing function, only if it mentions it in the capture list.
    - parameters and body are same as any function, it's just lambda's are like inline functions
    - lamda's can use static variables and variables defined outside the enclosing function directly with out capturing
    - return type should be mentioned by a trailing return type or can be infered based on the return statements in the body
    - return type is infered from the type of expression the return statement has, but it should be the only return statement in the body. If the body has more than one return statements and there is no explicit trailing return type, then the return type is inferred as void

    ex:- [num1](int a){ return num1 * a};
         [num1](int a)->int { return num1 * a}; 
        
    paranthesis and trailing return type can be omited, when omited paranthesis with empty parameter list is assumed.

### capture by value :  [names](){body}
    names represents the names of the local variable defined in the enclosing function, are captured by value when the lamda is defined not called
    any subsequent changes to the names outside lambda doesn't affect the value inside the lambda
    
### capture by reference : [& names](){body}
    when '&' symbol is used before a name, it is captured by reference

### mutable lamda
    - A lamda normaly is not allowed to change the value captured, but if we want the lamda to change then it needs to be declared 'mutable'.
    - 'mutable' keyword needs to follow '()' parantheses, incase there is a trailing return type, it needs to follow 'mutable' keyword not the other way around
    [name]() mutable ->return_type { body that modifies name }
    - paranthesis should not be omited when declaring mutable
    - captured value is changed by the lamda not the variable itself

    ex:-  int n = 10;
          auto f = [n]()mutable { return --n; };
        // now f has captured the value of n, so every time we call f(), the captured value is decremented
          auto val = f();
          val = f();
          val = f();  // after final call value will be 7
          std::cout << "value inside lambda = " << f()
                    << "\nvalue of n = " << n ;
                 
    output : 
            value inside lambda = 6
            value of n = 10

    lambda need not be mutable to change the global and static variables

### Implicit capture by value and capture by reference
    [=](){body}
    =, declared in catpure list makes the lambda captures all the local variables in the enclosing function by value by default
    [&](){body}
    &, declared in capture list makes the lambda captures all the local valriables in the enclosing function by reference by default

    Mixing implicit capture by value and reference
    [&,names](){body}  :  captures all local variables by reference except names
    [=, &names](){body} : captures all local variables by value except names which are captured by reference

    when we mix, the implicit capture by method should precede explicit captures

## bind(callable, args)
    - bind(), a function adapter that takes a callable and generates a new_callable.
    - when the new_callable is called, it calls the callable with its parameters as the arguments to the callable.
    - args... normaly consists of placeholders _n, where n is the place of the parameter int the parameter list of the new_callable.
            _1, represents the 1st parameter
            _2, reresents the 2nd parameter

    ex:-  auto f = bind(foo, _2, var1, _1, var2);
          f is the new callable generated by the bind()
          foo is the callable with 4 parameters
          _2 placeholder is binded to the 1st parameter of the foo
          _1 placeholder is binded to the 3rd parameter of the foo
          var1, var2 are the additional arguments passed from the accessible scope
          f() calls foo(), with its 1st param as 3rd arg and 2nd param as 1st arg, var1, and var2 as the arguments to foo

### binding reference
    normaly bind copies the names by value in to the newcallable, but if we want to use reference then the only way is to use
    ref() and cref()
    ref() takes an object and returns an new object which contains the reference of the original object
    cref() returns a const version ref()

## ITERATORS
- **INSERT ITERATOR**
- **STREAM ITERATOR**
- **REVERSE ITERATOR**
- **MOVE ITERATOR**

### INSERT ITERATOR 
    - back_insertor(iter) - returns a insert iterator which when assigned calls push_back() on a container.
        ex:- auto b_it = back_insertor(iter);
             *b_it = 45;  // calls push_back(45), b_it == *b_it
    
    - front_insertor(iter) - returns a insert iterator which when assigned calls push_front() on a contianer.
        ex:- auto f_it = front_insertor(iter);
             *f_it = 45;  // calls push_front(45), f_it = *f_it

    - insertor(iter) - returns a insert iterator which when assigned calls insert(iter,val) on a container, repeative        assignments will always call insert(iter, val), (ie) inserts always before the same iter. 
        ex:- auto i_it = insertor(iter);
             *i_it = 45  // calls insert(iter, 45), i_it == *i_it

### STREAM ITERATOR
#### iostream iterator  - acts as if iostream were a container (sequence of elements of type T)
     - istream_iterator - reads elements of Type T from the istream untill eof or invalid type
        ex:-  std::istream_iterator<T> i_iter(cin), end;  // i_iter initialised with cin to read elements of type T, 
                                                          // end default initialised which indicates eof and invalid input
              T val = *i_iter  // dereferencing returns value already read
              ++i_iter  // reads the next val in cin
              val = *i_iter++  // reads the next value and returns the old iter to dereference the previously read value

              std::vector<T> tvec(i_iter, end)  // initialises tvec with elements of type T from i_iter to end

     - ostream_iterator - writes an element of type T along with an optional string to ostream
        ex:-  std::ostream_iterator<T> o_iter(cout, " ");  // o_iter initialised with cout and an additional string_literal  
                                                           // to be written whenever o_iter writes to cout
                                                           // only character array and string_literal can be used
              o_iter = val  // writes val of type T to cout
                            // *o_iter, *o_iter++, o_iter++ these exists for style consistencies but functionaly does nothing

              val = *i_iter++  // reads the next val, returns old iter to dereference previous read value
              *o_iter++ = val  // writes val along with additional string if provided
              decrementing doesn't work.

              std::copy(tvec.cbegin(), tvec.cend(), o_iter)  // writes tvec from cbegin() to cend() in cout 

    istream_iterator<T> iter(cin)    -  reads a value of type T from cin
    istream_iterator<T> iter(ifile)  -  reads a value of type T from ifile,ifstream
    istream_iterator<T> iter(line)   -  reads a value of type T from string
    istream_iterator<T> end          -  default initialised to indicate eof or invalid input

    ostream_iterator<T> iter(cout, "\n")  - writes a value of type T along with additional string_literal to cout          
    ostream_iterator<T> iter(ofile, "\n") - writes to ofile,ofstream
    ostream_iterator<T> iter(line,"\n")   - writes to line,ostringstream 

### iostream vs iostream iterator
    iostream - makes io_object to be treated as a stream, a buffer of characters
        - istream in_strm(std::cin)    : in_strm >> val    // reads a element from cin, cin itself is a istream 
        - ifstream i_fstrm(file_name)  : i_fstrm >> val    // reads a element from file 
        - istringstream istr_strm(str) : istr_strm >> val  // reads a element from str 

        - ostream o_strm(std::cout)    : o_strm << val     // writes a element to cout, cout itself is a ostream
        - ofstream o_fstrm(file_name)  : o_fstrm << val    // writes a element to file 
        - ostringstream ostr_strm      : ostr_strm << val  // ostr_strm.str() returns contents written as a string

    iostream_iterator - behaves as if iostream is a container, so we can iterate through it 
        - istream_iterator<T> i_iter(std::cin)     
        - istream_iterator<T> i_iter(i_fstrm)  
        - istream_iterator<T> i_iter(ostr_strm)
                reads element of type T from the istream using '>>' operator defined by the type T, so the types should have the '>>' operator defined, or else it won't work

                val = *i_iter++   //  increaments to read the next value and returns the old iterator to dereference the previous read value, (--)decrement won't work
        - istream_iterator<T> end;  
                default initialised, which indicates eof and invalid input

##### [i_iter, end), indicates the range
        - std::vector<std::string> strvec(i_iter,end);
        - std::find(i_iter, end, val);

        - ostream_iterator<T> o_iter(std::cout, string_literal) 
        - ostream_iterator<T> o_iter(o_fstrm, string_literal)
        - ostream_iterator<T> o_iter(ostr_strm, string_literal)
                *o_iter++ = val  // writes val of type T to ostream along with string_literal, *,++ doen't do anything. Uses '<<' operator to write val, so the element type should have '<<' operator defined

#### o_iter acts as a destination iter            
    std::copy(strvec.cbegin(), strvec.cend(), o_iter)
#### USE IOSTREAMS, WHEN <<,>> REQUIRED
#### USE IOSTREAM_ITERATOR, WHEN NEED TO ITERATE OR TO USE ALGORITHMS
#### EXAMPLE :-  

    #include <fstream>
    #include <iostream>
    #include <iterator>
    #include <vector>
    #include <sstream>

    int main(){
    
        std::ifstream ifile("text1.txt");   //  ifile is filestream which can be used to read like cin from file "text1.txt"
        std::ofstream ofile("text2.txt");   //  ofile is filestream which can be used to write like cout to "text2.txt" 
    
        std::ostringstream o_strstream;     //  strings are writen to o_strstream using <<
        std::ostream_iterator<std::string> o_striter(o_strstream, "\n");  // o_striter wites to o_strstream along with "\n"; 
        std::istream_iterator<std::string> i_striter(ifile), end ; // i_striter reads string from ifile using >>
        std::vector<std::string> words(i_striter, end);  // words is initialised with contents by iterating i_striter

        ifile.clear();      
        ifile.open("text1.txt"); // file is reopened as iterator is at eof, clear() won't rewind iterator in file

        std::string line;
        while(getline(ifile, line)){   // reads a line from ifile - ifstream
            *o_striter++ = line;       // writes to o_strstream along with "\n" 
        }

        ofile << o_strstream.str();   //  writes string contained with o_strstream in ofile, ofstream

        return 0;
    }

## ITERATOR CATEGORIES
1. Input iterators
2. Output iterators
3. Forward iterators
4. Bidirectional iterators
5. Random Access iterators
```c++
    Input Iterators :
        - reads but doesn't write
        - single pass only
        - =, assignment operator, iterator can only be on the right hand side
        - ==, != to test equality between two iterators
        - ++, pre and post incrementing supported, but incrementing invalidates all other iterators, so the state of the iterator cannot be saved
        - *, dereference operator returns the element read
        - ->, memeber access operator, in short for (*iter).memeber, returns the member of the underlying object
        ex:- istream iterators are input iterators
             find(), count() requires input iterators
    Output iterators :
        - writes but doen't read
        - single pass only
        - =, assignment operator, iterator can only be on the left hand side
        - ==, != to test equality
        - ++, pre and post incrementing supported, but incrementing 
        - *, dereference operator, when a value assigned writes to the sequence
        ex:- ostream iterators are output iterators
             copy() requires output iterator as its 3rd argument
    Forward iterators :
        - supports all the operations of input and output iterators
        - multipass supported, but in only forward direction
        - read and write to the same element supported
        - state of the iterator can be saved for later access
        ex:- forward_list provides forward iterators
             replace algorithm requires forward iterator
    Bidirectional iterators :
        - supports all the operations of Forward iterators
        - multipass supported in both directions
        - --, pre and post decrement supported 
        ex:- reverse() requires bidirectional iterators
             all containers iterators except forward_list meets the requirements of bidirectional iterators
    Random Access Iterators :
        - supports all the operations of Bidirectional iterators
        - constant time access to all elements in the sequence
        - iterator arithmatic supported, - used between two iterators returns the distance of one from the other
        - -,+,-=,+= on the iterator and an integral
        - <, >, <=, >= relational operators are supported along with equality operators
        - [], subscript operator, in short of *(iter + n) to access element based on its element
        ex:- iterators of vector, array, string, deque and pointers of built-in array are random access iterators
             sort() requires random access iterators
```
## ALGORITHM PARAMETERS CONVENTION
    alg(beg, end, otherargs)
    alg(beg, end, dest, otherargs)      
    alg(beg, end, beg2, otherargs)
    alg(beg, end, beg2, end2, otherargs)
            - beg and end indicates the input range
            - dest, destination iterator which is assumed to be large enough to write the range, normally ostream_iterators are used
            - beg2, iterator to the second sequence, assumed to be large enough as the first range
            - beg2 and end2, indicates the second sequence for output

## CONTAINER SPECIFIC OPERATIONS
    list and forward list provides their own version of generic algorithms.
    when generic algorithms copies the values, these member versions copies or swaps the links of the elements, as a result
    these member specific version achieves much better performance than the generic ones.
    crucial difference is these member versions change the underlying containers.
        list.unique() erases all the adjasent duplicate elements
        list.merge() destroys the second sequence

        
    


            
 

0