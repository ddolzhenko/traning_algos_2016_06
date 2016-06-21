#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


int search(int A[], int size, int elem);
int search2(int A[], int size, int elem);
int binarySearch(int A[], int size, int elem);
int search_linear(int A[], int size, int elem);
int* min_search(int *b, int *e);

template <class TIter, class T>
TIter binary_searchD(TIter b, TIter e, const T& key);

template<class TIter, class T>
TIter binary_searchD2(TIter b, TIter e, const T & key);

template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T & key);

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
		<< param1 << ", " << param2 << ")\n";
	std::cout << string(80, '-')
		<< (expected != res ? "fail" : "ok") << std::endl;
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key) {
		if(v.size() == 0)
			return base_search_func((int*)&v, v.size(), key);
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
	test(3, search_func, Vec({ 1, 56, 99, key, 45, -100 }), key);
}

void test_search()
{
	cout << "Simple Linear Search:\n";
	test_search_general(search_linear);
	cout << "\nSearch 3:\n";
	test_search_general(search2);

	cout << "\nBinary Search:\n";
	test_search_general(binarySearch);
}

int main()
{
	//test_search();
	const int size = 5;
	int arr[size] = { 1,2,3,4,5 };
	int arr2[1] = {1};

	int *ptr = NULL;

	//cout << ">>>>>>>>>>>>>>>>>>" << min_search(ptr, 1) << endl;
	
	while (true);
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

int* min_search(int *b, int *e)
{ 
	int *min = b;
	while (b < e)
	{
		if (*b < *min)
			*min = *b;
		++b;
	}

	return min;
}

int search(int A[], int size, int elem)
{
	assert(A != 0);
	assert(size >= 0);
	A[size] = elem;

	int i = 0;

	while (A[i] != elem)
		++i;

	if (i != size)
		return i;
	
	return -1;
}

int search2(int A[], int size, int elem)
{
	assert(A != 0);
	assert(size >= 0);
	int ind = -1;
	if (A[size-1] == elem)
		ind = size - 1;
	
	int lastElem = A[size - 1];
	
	A[size - 1] = elem;

	int i = 0;
	while (A[i] != elem)
		++i;
	
	if (i < (size-1))
		ind = i;

	A[size - 1] = lastElem;
	
	return ind;
}

int bin_search(int A[], int min, int max, int elem)
{
	int ind = min + (max - min) / 2;
	
	
	if (elem == A[ind -1])
		return ind -1;
	if (elem == A[max - 1])
		return max - 1;
	if (ind == 0 || ind == min)
		return -1;
	else if (elem < A[ind -1])
		ind = bin_search(A, min, ind, elem);
	else if (elem > A[ind - 1])
		ind = bin_search(A, ind, max, elem);
	
	return ind;
}
int binarySearch(int A[], int size, int elem)
{
	assert(A != 0);
	assert(size >= 0);
	int res = bin_search(A, 0, size, elem);
	return res;
}

template<class TIter, class T>
TIter binary_searchD(TIter b, TIter e, const T & key)
{
	assert(std::is_sorted(b, e));
	auto end = e;
	while (b < e)
	{
		TIter m = b + (e - b) / 2;
		// [b, m) U [m] U [m+1, e)
		if (key < *m)
			e = m;
		else if (key > *m)
			b = m+1;
		else
			return m;
	}
		
	return end;
}

template<class TIter, class T>
TIter binary_searchD2(TIter b, TIter e, const T & key)
{
	auto lb = lower_bound(b, e, key);

	if (lb != e && *lb == key)
		return lb;
	return e;
}

template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T & key)
{
	assert(std::is_sorted(b, e));
	while (b < e)
	{
		TIter m = b + (e - b) / 2;
		// [b, m) U [m] U [m+1, e)
		if (key < *m)
			e = m + 1;
		else
			e = m;
	}

	return b;
}