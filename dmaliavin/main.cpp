#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
using namespace std;

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

