#include <vector>
#include <iostream>


template <class TValue>
class evenPredicate {  
public:  
  bool operator()(TValue v)  
  { return (v % 2 == 0); }  
}; 


template <class TValue>
bool even(TValue V)
{
    return (V % 2 == 0);
}

template <class TIter, typename F>
TIter remove_IF(TIter b, TIter e, F f)
{
    // b < e

    // [b, e)
    auto it = b;
    auto itRightEnd = b;
    
    while (it != e)  
    {
        // [b, itRightEnd) U [itRightEnd, it) U [it, e)
        // [b, itRightEnd) has no elements with f() == true
        
        if ( !f(*it) )
        {
            *itRightEnd = *it;
            ++itRightEnd;
        }
/*
        if ( f(*it) )
        {
            ++it;
        }
*/        

        ++it;
    }

    return itRightEnd;
};



int main()
{
    std::vector<int> v({0, 1, 12, 40, 33, 56, 23, 0});

   // auto itIF = remove_IF(v.begin(), v.end(), even<int>);

    auto itIF = remove_IF(v.begin(), v.end(), [] (auto val) { return (val % 2 == 0); } );

    for (auto i: v)
    {
        std::cout << i << ' ';
    }

    std::cout << "\n";

    for (auto it = v.begin(); it < itIF; ++it)
    {
        std::cout << *it << ' ';
    }    

    return 0;
}