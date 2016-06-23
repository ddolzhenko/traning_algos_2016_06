#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>

int binarySearch(int A[], int size, int key);

//test framework
template<class TExpect, class TFunc, class TParam1, class TParam2> 
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
	auto actual = f(param1, param2);
	if (expected != actual)
	{
		cout<<"\n expected "<< expected << " , but was " << actual << "\n";
	}
	else
	{
		cout << "OK\n";
	}
}

template<class TFunc>
void testSearchGeneral(TFunc baseSearchFunc)
{
	auto searchFunc = [=](std::vector<int> v, int key)
	{
		return baseSearchFunc(&v[0], v.size(), key);
	};
	int key = 42;

	//key not in array
	test(-1, searchFunc, std::vector<int>(), key);
	test(-1, searchFunc, std::vector<int>({1}), key);
	test(-1, searchFunc, std::vector<int>({1,2}), key);
	test(-1, searchFunc, std::vector<int>({1,2,3,4,5}), key);

	//key in array
	test(0, searchFunc, std::vector<int>({key}), key);
	test(0, searchFunc, std::vector<int>({key, 100}), key);
	test(1, searchFunc, std::vector<int>({1, key}), key);
	test(0, searchFunc, std::vector<int>({key,100,200,300,400}), key);
	test(4, searchFunc, std::vector<int>({1,2,3,4,key}), key);
}

void testSearch()
{

	testSearchGeneral(binarySearch);
}

int main()
{
	testSearch();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////

int binarySearch(int A[], int size, int key)
{
    assert(size>=0);
    assert(std::is_sorted(A, A+size));
    if (size == 0) return -1;

    int middle = size/2;
    if (key < A[middle])
    {
        return binarySearch(A, middle, key);
    }
    else if (A[middle] < key)
    {
        return middle + 1 + binarySearch(A + middle + 1, size - middle - 1, key);
    }
    else
    {
        return middle;
    }
}

template<class TIter, class T>
TIter binarySearch(TIter b, TIter e, const T& key)
{
    assert(std::is_sorted(b, e));
    auto end = e;
    while(b < e)
    {
        TIter m = b + (e-b)/2;
        if (key < *m)
        {
            e = m;
        }
        else if (*m < key)
        {
            b = m;
        }
        else
        {
            return m;
        }
    }

    return end;

} 

template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T& key)
{
    while(b < e)                //1
    {
        TIter m = b + (e-b)/2;  //3
        if (*m < key)           //2
        {
            b = m+1;            
        }
        else
        {
            e = m;
        }                       //1
    }
    return b;
}

template<class TIter, class T>
TIter binarySearchLowerBound(TIter b, TIter e, const T& key)
{
    
    auto lb = lower_bound(b, e, key);   //3

    if (lb != e && *lb == key)          //3
        return lb;
    return e;                           //1

    //7*log(n) + 7
    

} 

template<class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T& key)
{
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




