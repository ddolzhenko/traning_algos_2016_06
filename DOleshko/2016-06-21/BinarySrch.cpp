
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

template <class TIter, class T>
TIter binary_search(TIter b, TIter e, const T& key)
{
    assert(std::is_sorted(b, e));
    auto end = e;

    while (b < e)
    {
        TIter m = b + (e-b)/2; // prove that m IS INSIDE b...e
        // [b, m) U [m] U [m+1, e)
        if (key < *m)
        {
            e = m;         // [b, m)
        }
        else if (*m < key) // we used ONLY < operation !!!!
        {
            b = m + 1;     // [m+1, e)
        }
        else
        {
            return m;      // [m]
        }
    }

    // now b == e and it is a place where to insert a KEY if it is absent

    return end;
}


template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
    auto result = f(param1, param2);
    std::cout << "\ntesting: " << expected << " = " << "f (" << param1 << ", " << param2 << ")" << std::endl;
    std::cout << std::string(40, '-') << (expected != result ? "FAIL\n" : "OK\n");
}

template<class TFunc>
void test_search_binary(TFunc base_search_func)
{
    auto search_func = [=](std::vector<int> v, int key)
    {
        //return base_search_func(&v[0], v.size(), key);
        if(v.size() == 0)
        {
            return base_search_func(0, 0, key);
        }
        else
        {
            return base_search_func(&v[0], v.size(), key);
        }
    };

    int key = 77;
    typedef std::vector<int> Vec;

    //key not in array
        //degenerated
        test(-1, search_func, std::vector<int>(), key);

        //trivial
        test(-1, search_func, Vec({1}), key);
        test(-1, search_func, Vec({80}), key);

        //normal
        test(-1, search_func, Vec({-80, 95, 106, 142}), key);

    //key not in array
        //trivial
        test(0, search_func, Vec({key}), key);
        test(1, search_func, Vec({-87, key}), key);

        //normal
        test(0, search_func, Vec({key, 80, 86, 92}), key);
        test(2, search_func, Vec({10, 35, key, 86, 92}), key);
        test(4, search_func, Vec({10, 35, 56, 72, key}), key);
}

void test_search()
{
    test_search_binary(binarySearch);
    //std::cout << std::string(10, '*') << std::endl;
    //test_search_binary(binarySearchRec);
}

std::ostream& operator<<(std::ostream& o, const std::vector<int>& data)
{
    o << "{";
    for(const auto& x : data)
    {
        o << x << ", ";
    }

    return  o << "}";
}

int main (void)
{

    test_search();

    return 0;
}
