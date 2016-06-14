#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;

int linearSearchBasic(int A[], int size, int key);
int linearSearchAddNew(int A[], int size, int key);
int linearSearchAddNewOutOfMemory(int A[], int size, int key);

//tests
void testLinearSearchAddNewOutOfMemoryOK();
void testLinearSearchAddNewOutOfMemoryNoElem();
void testLinearSearchAddNewOutOfMemoryEmptyArray();

void testLinearSearchBasicOK();
void testLinearSearchBasicNoElem();
void testLinearSearchBasicEmptyArray();

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
	test(0, searchFunc, std::vector<int>({key, 1}), key);
	test(1, searchFunc, std::vector<int>({1, key}), key);
	test(0, searchFunc, std::vector<int>({key,1,2,3,4}), key);
	test(4, searchFunc, std::vector<int>({1,2,3,4,key}), key);
}

void testSearch()
{

	testSearchGeneral(linearSearchBasic);
}

int main()
{
	// testLinearSearchAddNewOutOfMemoryOK();
	// testLinearSearchAddNewOutOfMemoryNoElem();
	// testLinearSearchAddNewOutOfMemoryEmptyArray();

	// testLinearSearchBasicOK();
 // 	testLinearSearchBasicNoElem();
 // 	testLinearSearchBasicEmptyArray();
	testSearch();
    return 0;
}

int linearSearchBasic(int A[], int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (A[i] == key)
		{
			return i;
		}
	}
	return -1;
}

int linearSearchAddNew(int A[], int size, int key)
{
	A[size] = key;
	int i = 0;

	while(A[i] != key)
	{
		i++;
	}

	if (i==size)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

int linearSearchAddNewOutOfMemory(int A[], int size, int key)
{
	assert(A != 0);
	assert(size >= 0);

	if (size == 0)
	{
		return -1;
	}

	int last = A[size-1];
	A[size-1] = key;
	int i = 0;

	while(A[i] != key)
	{
		i++;
	}

	if (i==size-1)
	{
		if (last == key)
		{
			return size-1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return i;
	}
}

void testLinearSearchAddNewOutOfMemoryOK()
{
	int size = 3;
    int A [size] = { 16, 3, 77 };
    int index = linearSearchAddNewOutOfMemory(A, size, 3);
    if (index == 1)
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryOK - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryOK - Failed";
    }
    
}

void testLinearSearchAddNewOutOfMemoryNoElem()
{
	int size = 3;
    int A [size] = { 16, 3, 77 };
    int index = linearSearchAddNewOutOfMemory(A, size, 33);
    if (index == -1)
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryNoElem - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryNoElem - Failed";
    }
    
}

void testLinearSearchAddNewOutOfMemoryEmptyArray()
{
	int size = 0;
    int A [size] = {};
    int index = linearSearchAddNewOutOfMemory(A, size, 33);
    if (index == -1)
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryEmptyArray - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchAddNewOutOfMemoryEmptyArray - Failed";
    }
    
}

void testLinearSearchBasicOK()
{
	int size = 3;
    int A [size] = { 16, 3, 77 };
    int index = linearSearchBasic(A, size, 3);
    if (index == 1)
    {
    	cout << "\ntestLinearSearchBasicOK - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchBasicOK - Failed";
    }
    
}

void testLinearSearchBasicNoElem()
{
	int size = 3;
    int A [size] = { 16, 3, 77 };
    int index = linearSearchBasic(A, size, 33);
    if (index == -1)
    {
    	cout << "\ntestLinearSearchBasicNoElem - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchBasicNoElem - Failed";
    }
    
}

void testLinearSearchBasicEmptyArray()
{
	int size = 3;
    int A [size] = {};
    int index = linearSearchBasic(A, size, 33);
    if (index == -1)
    {
    	cout << "\ntestLinearSearchBasicEmptyArray - Passed";
    }
    else
    {
    	cout << "\ntestLinearSearchBasicEmptyArray - Failed";
    }
    
}

