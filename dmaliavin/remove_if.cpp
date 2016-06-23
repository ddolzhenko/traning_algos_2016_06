#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>

int* remove_even(int* first, int* last)
{
    assert(first <= last);
    int* res = first;
    while(first != last)
    {
        if(*first % 2 != 0)
        {
            *res = *first;
            res++;
        }
        first++;
    }
    return res;
}

int main()
{
    int size = 4;
    int A[] = {6, 12,2,32,4};
    int* res = remove_even(A, A+size);
    for(int* p = A; p != res; p++)
    {
        std::cout<< *p << "\n";
    }
    return 0;
}