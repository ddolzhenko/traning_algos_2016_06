#include "stdafx.h"
#include <iostream>

using namespace std;

int search1(int A[], int size, int key)
{
	for (int i = 0; i < size; ++i)
		if (key == A[i])
			return i;
	return -1;
}

int search2(int A[], int size, int key)
{
	if (size < 1)
		return -1;

	A[size] = key;
	int i = 0;
	while (A[i] != key)
	{
		++i;
	}
	if (size != i)
		return i;

	return -1;
}

int search3(int A[], int size, int key)
{
	if (size < 1)
		return -1;

	int last_index = size - 1;
	int last_element = A[last_index];

	if (last_element == key)
		return last_index;

	A[last_index] = key;

	int i = 0;
	while (A[i] != key)
	{
		++i;
	}

	A[last_index] = last_element;

	if (last_element != i)
		return i;

	return -1;

}

int main()
{

	int A[] = {1,2,3,4,5};

	cout << "Search 1:" << search1(A, 5, 3) << endl;
	cout << "Search 2:" << search2(A, 5, 3) << endl;
	cout << "Search 3:" << search3(A, 5, 3) << endl;

	system("pause");
	return 0;
}
