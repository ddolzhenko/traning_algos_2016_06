#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>

template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T& key)
{
    assert(b <= e); // contract
    while(b < e)
    {
        TIter m = b + (e-b)/2;
        if (*m < key)
        {
            b = m+1;
        }
        else
        {
            e = m;
        }
    }
    return b;
}

template<class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T& key)
{
    assert(b <= e);
    while(b < e)
    {
        TIter m = b + (e-b)/2;
        if (key < *m)
        {
            e = m;
        }
        else
        {
            b = m+1;
        }
    }
    return b;
}

template<class TIter>
void count_7(A[] array)
{
    int key = 7;
    return upper_bound(b, e, key) - lower_bound(b, e, key);
}

int main()
{
    int A[] = {1,2,3};
    std::cout << "2";
    return 0;
}