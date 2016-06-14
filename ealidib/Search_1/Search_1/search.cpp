#include <iostream>


int search(int* A, int size, int elem);
int search2(int* A, int size, int elem);

int main()
{
	const int size = 5;
	int arr[size] = { 1,2,3,4,5 };

	int elem = 5;
	int ind = search(arr, size, elem);

	std::cout << "First search:\n";
	if (ind == -1)
		std::cout << "Elem " << elem << " doesn't exist.\n";
	else
		std::cout << "index of elem " << elem << " = " << ind << std::endl;

	std::cout << "Second search:\n";
	ind = search2(arr, size, elem);
	if (ind == -1)
		std::cout << "Elem " << elem << " doesn't exist.\n";
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

int search2(int* A, int size, int elem)
{
	if (A[size-1] == elem)
		return (size - 1);
	
	int lastElem = A[size - 1];
	
	A[size - 1] = elem;

	int i = 0;
	while (A[i] != elem)
		++i;

	int ind = -1;
	if (i != (size-1))
		ind = i;

	A[size - 1] = lastElem;
	
	return ind;
}
