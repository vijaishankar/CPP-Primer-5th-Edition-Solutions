# Sequential Containers
    A container holds a collection of objects of a similar type. The sequencial containers lets the programmer control the order in which the elements are stored and accessed, but order does't depend on the values instead it corresponds to the
    position at which the elements are put in to the container.       
        vector - flexible sized array
                 supports fast random access, subscripts can be used
                 insertion or deletion other than the back will be slow
        deque  - double ended queue
                 supports fast random access,
                 fast insertion and deletion at the front and back
        list   - doubly linked list
                 fast insertion and deletion at anywhere in the container
                 no random access, only bidirectional access,  iterates through the elements
        forward_list - singly linked list
                 sequencial access in one direction
                 fast insertion and deletion at any point
        array  - fixed sized array
                 supports random access
                 cannot add or remove items
        string - vector like container that stores only characters
                 fast insertion and deletion at the back
                 fast random access
    Any container can hold any type including another container as its elements, But container operations(member functions) imposes their own restrictions for what types they can be used
        ex :- a type with no constructor
               vector<noDefault> vec1(10, init)  // ok : init is used to construct the elements
              vector<noDefault> vec2(10)        // error : as noDefault as no default constructor, vec2 won't be able to     
                                                           constructs objects






 


            