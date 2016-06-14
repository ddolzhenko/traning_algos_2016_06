
#include <iostream>

int search_1(int M[], int size, int key)
{
	std::cout << "search_1 : key = " << key << std::endl;
	for(int i=0; i<size; ++i)
	{
		if(M[i] == key)
			return i;
	}

	return -1;
}

int search_2(int M[], int size, int key)
{
	std::cout << "search_2 : key = " << key << std::endl;
	int i=0;
	M[size] = key;
	while(M[i] != key)
	{
		++i;
	}

	if(i != size)
	{
		return i;
	}

	return -1;
}

int search_3(int M[], int size, int key)
{
	 std::cout << "search_3 : key = " << key << std::endl;
	 if(M[size-1] == key)
	 {
	 	return size-1;
	 }
	
	int i = 0;
	int last = M[size-1];
	M[size-1] = key;

	while(M[i] != key)
	{
		++i;
	}

	M[size-1] = last;

	if(i != size-1)
	{
		return i;
	}

	return -1;
}

void printArr(int M[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << "[" << i << "]= " << M[i] << std::endl;
	}
}

int EMPTY [6];

int main (void)
{
	int i = 0;

	int A [6] = {1,2,3,4,5,0};
	std::cout << "****************" << std::endl;
	printArr(A, 6);
	std::cout << search_1(A, 5, 4) << std::endl;
	std::cout << search_2(A, 5, 2) << std::endl;
	std::cout << search_2(EMPTY, 5, 7) << std::endl;
	std::cout << search_3(A, 5, 5) << std::endl;
	std::cout << search_3(A, 5, 7) << std::endl;
	std::cout << search_3(EMPTY, 6, 7) << std::endl;


	return i;
}


