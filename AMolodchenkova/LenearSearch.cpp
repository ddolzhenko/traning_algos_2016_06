#include <iostream>
//#include <assert>
#include <string>
#include <vector>
using namespace std;

int linearSearch_1(int arr[], int size, int key)
{
    for(int i = 0; i < size; i++ )
    {
        if(arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int linearSearch_2(int arr[], int size, int key)
{
    arr[size] = key;

    int i = 0;
    while (arr[i] != key)
    {
        i++;
    }

    if(i != size)
    {
        return i;
    }
    return -1;
 }

int linearSearch_3(int arr[], const int& size, const int& key)
{
/*   int last = arr[size-1];
    arr[size-1] = key;

    while (arr[i] != key)
    {
        i++;
    }
    if (arr[i] == key)
    {
        return i;
    }

    if(last != key)
    {
        return -1;
    }
    return -1;
*/
 }

template <class TExpected, class TFunc, class TParam1, class TParam2>
void test (TExpected expected, TFunc f, TParam1 param1, TParam2 param2)
 {
    auto result = f(param1, param2);
    cout << "testing: " << expected << "==" << "F(" << param1 << "," << param2 << ")" << endl;
    cout << string (80, "-") << (expected != result) ? "fail" : "ok" << endl;
 }

 ostream& operator<< (ostream& o, const std::vector<int>& data)
 {
    0<<"{";
    for (const auto&x: data)
    {
        o << x << ",";
    }
    return o<<"}";
 }

/*template <class TFunc>
void test_search(TFunc search_func)
{
    int key = 42;

    typedef std::vector<int> Vec;
    //key not in array
    test(-1, search_func, Vec, key );

    //trivial
    test(-1, search_func, {key}, key );

       //trivial 2nd
    test(-1, search_func, {1,key}, key );
    test(-1, search_func, {key,2}, key );
    test(-1, search_func, {key,key}, key );

    //usual
    test(-1, search_func, {key,2, 23,  54, 6} , key );
    test(-1, search_func, {1,  2, -80, 5,  key}, key );
    test(-1, search_func, {1,  2, key, 90, 3}  , key );
}*/

template <class TFunc>
void test_general(TFunc base_search_func)
{
    auto search_func = [=] (std::vector<int> v, int key)
    {
        return base_search_func(&v[0], v.size(), key);
    }

    typedef std::vector<int> Vec;
    //key not in array
    test(-1, search_func, Vec, key );

    //trivial
    test(-1, search_func, {key}, key );

       //trivial 2nd
    test(-1, search_func, {1,key}, key );
    test(-1, search_func, {key,2}, key );
    test(-1, search_func, {key,key}, key );

    //usual
    test(-1, search_func, {key,2, 23,  54, 6} , key );
    test(-1, search_func, {1,  2, -80, 5,  key}, key );
    test(-1, search_func, {1,  2, key, 90, 3}  , key );
}

int main ()
{
    int arr[6] = {2,4,6,7,9};

    cout<<"search: "<< linearSearch_1(arr, sizeof(arr)/sizeof(int), 6) <<endl;
    cout<<"search: "<< linearSearch_2(arr, sizeof(arr)/sizeof(int), 6) <<endl;

    test_general(linearSearch_1);

    return 0;
}