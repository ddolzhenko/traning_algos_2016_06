#include <iostream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

int binary_search_1(int A[], int size, int key) {
    //assert(size>=0);
    //assert(std::is_sorted(A, A+size));
    
    if(size == 0)
    {
        return -1;
    }

    int m = size / 2;
    if(key < A[m])
    {
        return binary_search_1(A, m, key);
    }
    else if (A[m] < key)
    {
        int result =  binary_search_1(A+m+1, size-m-1, key);
        return (result != -1) ? m+1+result : -1;
    }
    else
    {
        return m;
    }
}


int binary_search_2(int A[], int size, int key) {
    //assert(size>=0);
    //assert(std::is_sorted(A, A+size));
    
    int n = 0;
    while(size != 0)
    {
        // [0, m)[m][m+1, size)
        int m = size/2;
        if(key < A[m])
        {
            size = m;   // [0, m)
        }
        else if (A[m] < key)
        {
            n = m + 1;
            A = A + n;  // [m+1, size)
            size -= n;
        }
        else
        {
            return m+n;
        }
    }

    return -1;
}
/*----------------------------------------------------------------------*/

template <class TExpected, class TFunc, class TParam1, class TParam2>
void test (TExpected expected, TFunc f, TParam1 param1, TParam2 param2)
 {
    auto result = f(param1, param2);
    cout << "testing: " << expected << "==" << result << "(F(" << param1 << "," << param2 << "))" << endl;
    cout << string (80, '-') << ((expected != result) ? "fail" : "ok") << endl;
 }

 ostream& operator<< (ostream& o, const std::vector<int>& data)
 {
    o << "{";
    for (const auto&x: data)
    {
        o << x << ",";
    }
    return o << "}";
 }

template <class TFunc>
void test_general(TFunc base_search_func)
{
    auto search_func = [=] (std::vector<int> v, int key)
    {
        return base_search_func(&v[0], v.size(), key);
    };

    int key = 42;
    typedef std::vector<int> Vec;
    
    //key not in array
    test(-1, search_func, Vec(), key );
    //trivial
    test(-1, search_func,  Vec({1}), key );

       //trivial 2nd
    test(-1, search_func, Vec({1,23}), key );
    test(-1, search_func, Vec({-80,2}), key );
    test(-1, search_func, Vec({20,23}), key );

    //usual
    test(-1, search_func, Vec({-3,2, 23,  54, 60}), key );
    test(-1, search_func, Vec({1,  2, 4, 5, 98}), key );
    test(-1, search_func, Vec({1,  2,  10, 90, 300}), key );

    //key in array
    //trivial
    test(0, search_func,  Vec({key}), key );

       //trivial 2nd
    test(1, search_func, Vec({1,key}), key );
    test(0, search_func, Vec({key,200}), key );
    test(0, search_func, Vec({key,key}), key );

    //usual
    test(0, search_func, Vec({key,43, 63,  89, 600}), key );
    test(4, search_func, Vec({1,  2, 4, 5,  key}), key );
    test(2, search_func, Vec({1,  2, key, 90, 300}), key );
}

int main ()
{
    test_general(binary_search_1);
    //test_general(binary_search_2);
    return 0;
}
