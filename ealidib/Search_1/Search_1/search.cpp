#include <iostream>


int search(int* A, int size, int elem);

int main()
{
	const int size = 5;
	int arr[size] = { 1,2,3,4,5 };

	int elem = arr[0];
	int ind = search(arr, size, elem);

	if (elem == -1)
		std::cout << "Elem " << elem << "doesn't exist.\n";
	else
		std::cout << "index of elem " << elem << " = " << ind << std::endl;

	while (true) {}
	
	return 0;
}

int search(int* A, int size, int elem)
{
	A[size] = elem;

	int i = 0;

	while (A[i] != elem)
		++i;

	if (i != size)
		return i;
	
	return -1;
}