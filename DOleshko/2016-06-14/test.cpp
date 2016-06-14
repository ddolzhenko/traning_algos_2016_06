
#include <iostream>

int search_1(int A[], int size, int key)
{
	for(int i=0; i<size; ++i)
	{
		if(A[i] == key)
			return i;
	}

	return -1;
}

int search_2(int A[], int size, int key)
{
	int i=0;
	A[size] = key;
	while(A[i] != key)
	{
		++i;
	}

	if(i != size)
	{
		return i;
	}

	return -1;
}

int search_3(int A[], int size, int key)
{/*
	int i=0;
	int end = A[size];
	 = key;
	


	while(A[i] != key)
	{
		++i;
	}

	if(i != size)
	{
		return i;
	}*/

	return -1;
}

void printArr(int A[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << "A[" << i << "]= " << A[i] << std::endl;
	}
}

int main (void)
{
	int i = 0;

	int A [6] = {1,2,3,4,5,0};
	std::cout << search_1(A, 5, 4) << std::endl;
	std::cout << search_2(A, 6, 7) << std::endl;
	printArr(A, 6);

	return i;
}


