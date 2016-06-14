#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


int search(int* A, int size, int elem);
int search2(int* A, int size, int elem);
int binarySearch(int* A, int size, int elem);
int search_linear(int A[], int size, int elem);

ostream& operator<<(ostream& o, const std::vector<int>& data)
{
	o << "{";
	for (const auto & x : data)
		o << x << ", ";
	return o << "}";
}
template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
	auto res = f(param1, param2);

	std::cout << "testing: " << expected << " == " << "f("
		<< param1 << ", " << param2 << ")/n";
	std::cout << string(80, '-')
		<< (expected != res ? "fail" : "ok") << std::endl;
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key) {
		return base_search_func(&v[0], v.size(), key);
	};

	typedef std::vector<int> Vec;
	int key = 42;
	//key not in array
	//degenerated:
	test(-1, search_func, Vec(), key);

	//trivial:
	test(-1, search_func, Vec({ 56 }), key);

	//trivial2nd:
	test(-1, search_func, Vec({ 1,1 }), key);
	test(-1, search_func, Vec({ 1, 2 }), key);
	test(-1, search_func, Vec({ 2,1 }), key);

	//normal
	test(-1, search_func, Vec({ 1, 56, 99, 45 }), key);
	test(-1, search_func, Vec({ 1, 56, 99, 45, -100 }), key);

	//key in array
	//trivial:
	test(0, search_func, Vec({ key }), key);

	//trivial2nd:
	test(1, search_func, Vec({ 1,key }), key);
	test(0, search_func, Vec({ key, 2 }), key);
	test(0, search_func, Vec({ key,key }), key);

	//normal
	test(0, search_func, Vec({ key, 56, 99, 45 }), key);
	test(5, search_func, Vec({ 1, 56, 99, 45, -100, key }), key);
	test(5, search_func, Vec({ 1, 56, 99, key, 45, -100 }), key);
}

void test_search()
{
	test_search_general(search_linear);
}

int main()
{
	test_search();
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

int search_linear(int A[], int size, int elem)
{
	assert(size >= 0);

	for (auto i = 0; i < size; ++i)
	{
		if (A[i] == elem)
			return i;
	}

	return -1;
}

int search(int* A, int size, int elem)
{
	//assert(A != 0);
	//assert(size >= 0);
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
	//assert(A != 0);
	//assert(size >= 0);
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

int binarySearch(int* A, int size, int elem)
{
	return -1;
}
