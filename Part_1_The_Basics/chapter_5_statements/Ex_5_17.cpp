/*  Exercise 5.17: Given two vectors of ints, write a program to determine whether one vector is a prefix of the other. For 
 *  vectors of unequal length, compare the number of elements of the smaller vector. For example, given the vectors 
 *  containing 0,1, 1, and 2 and 0, 1, 1, 2, 3, 5, 8, respectively your program should return true */

#include <iostream>
#include <vector>

int main(){
    std::vector<int> ivec1;
    std::vector<int> ivec2;

    //  code to get numbers for ivec1
    std::cout << "Enter the first set of numbers[0 to submit] : \n";
    int num;
    while(std::cin >> num){
        if(!num){
            break;
        }
        ivec1.push_back(num);
    }

    //  code to get numbers for ivec2
    std::cout << "Enter the second set of numbers[0 to submit] : \n";
    while( std::cin >> num ){
        if(!num){
            break;
        }
        ivec2.push_back(num);
    }

    /*  code to find which vector is smaller, so the smaller one is checked against the bigger one
     *  since swaping the vectors might be heavy if larger number of items present, the code stores iterators for smaller
     *  vector and bigger vectors */

    size_t szSmall, szBig; 
    std::string subVector,bigVector; 
    std::vector<int>::const_iterator begSmall, endSmall, begBig, endBig;
    if( ivec1.size() < ivec2.size() ){
        begSmall = ivec1.cbegin();
        endSmall = ivec1.cend();
        begBig = ivec2.cbegin();
        endBig = ivec2.cend();
        szSmall = ivec1.size();
        szBig = ivec2.size();
        subVector = "ivec1";
        bigVector = "ivec2";
    }else{
        begSmall = ivec2.cbegin();
        endSmall = ivec2.cend();
        begBig = ivec1.cbegin();
        endBig = ivec1.cend();
        szSmall = ivec2.size();
        szBig = ivec1.size();
        subVector = "ivec2";
        bigVector = "ivec1";
    }

    bool found = true;
    int pos = 0;
    int index = 0;

    // code to find the position where the first element of smaller vector is found in bigger vector
    while((begBig != endBig) && (*begSmall != *begBig)){
        ++pos;
        ++begBig;
    }
    index = pos;

    /*  code to check if all elements of smaller vector is found in bigger vector
     *  begBig == endBig then, no match was found or if no of elements in bigger vector is lesser than smaller vector, then
     *  we conclude there is no sub vector */ 
    if(begBig != endBig && ( szSmall <= (szBig - pos ))){           
        std::cout << "inside matching element by element, index found at : "<< index << std::endl;
        for( ; begSmall != endSmall; ++begSmall, ++begBig){
            std::cout << "\ncomparing "<< *begSmall << " and " << *begBig;
            if( *begSmall != *begBig){
                found = false;
                break;
            }
        }       
    }else{
        found = false;
    }


    std::cout << std::endl;
    if( found ){
        std::cout << subVector << " found at index " << index << " of " << bigVector << " vector" << std::endl;
    }else{
        std::cout << subVector << " not found in " << bigVector << std::endl; 
    }

    return 0;
}
