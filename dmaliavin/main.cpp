#include <iostream>
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

int main()
{
	testLinearSearchAddNewOutOfMemoryOK();
	testLinearSearchAddNewOutOfMemoryNoElem();
	testLinearSearchAddNewOutOfMemoryEmptyArray();

	testLinearSearchBasicOK();
 	testLinearSearchBasicNoElem();
 	testLinearSearchBasicEmptyArray();
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
	int size = 3;
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

