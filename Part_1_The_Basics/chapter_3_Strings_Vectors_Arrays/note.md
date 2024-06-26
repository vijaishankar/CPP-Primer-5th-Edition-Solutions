# STRING    
> **string literals** like "hello" and **string** library type are two different types.
> **getline(istream, str)**, reads the *istream* upto and including *newline* character and discards the *newline*, stores the rest in *str*.

## subscript
> **subscript operator,[]** takes a ***std::string::size_type***( which is unsigned, any -ve integral will be converted)
> subscripting the *empty string* and outside the range is **undefined**, so before accessing a char in a string it should be checked that the string is not empty

## iterator
> **begin()** and **end()** returns normal iterator which can read and writes to the container
> **cbegin()** and **cend()** returns const std::container_type::iterator type which can only read but not write, simply  an iterator to const
> **iterator - iterator = difference_type**, every container that supports subraction operator has defined companion type std::vector<type>::iterator::difference_type.
> **pointer - pointer = ptrdiff_t**, defined in cstddef header