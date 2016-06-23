#include <vector>


template <class TValue>
class evenPredicate {  
public:  
  bool operator()(TValue v)  
  { return (v % 2 == 0); }  
}; 


template <class TIter, evenPredicate>
TIter remove_IF(TIter b, TIter e, evenPredicate f)
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

    return b;
};

template <class TValue>
bool even(TValue V)
{
    return (*V % 2 == 0);
}

int main()
{
    std::vector<int> v({0, 1, 12, 40, 33, 56, 23, 0});

    return 0;
}