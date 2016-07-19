#include "radix_sort.h"


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

template<class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T & key);

template<class TIter, class T>
size_t count_7(TIter b, TIter e);

template<class TIter>
void bubble_sort(TIter b, TIter e);


int* my_lower_bound(int* b, int* e, const int & key);
int* my_upper_bound(int* b, int* e, const int & key);
size_t count_7(int* b, int* e);

size_t remove_even(int* b, int* e, int value);
void sort_pair(int * b, int * e);

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
	const int size = 6;
	int arr[size] = { 1,6,8,3,4,5 };

	/*int new_size = remove_even(arr, arr + size, 2);

	cout << "new_size: " << new_size << endl;
	for (int i = 0; i < new_size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;*/

	int size2 = 5;
	int * arr2 = new int[size2];
	arr2[0] = 2;
	arr2[1] = 8;
	arr2[2] = 10;
	arr2[3] = -1;
	arr2[4] = 0;
	
	sort_pair(arr2, arr2 + size2);

	for (int i = 0; i < size2; i++)
	{
		cout << arr2[i] << " ";
	}
	cout << " ::end" << endl;
	
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
TIter binary_searchD2(TIter b, TIter e, const T & key) // v(2)  &(1)
{
	auto lb = lower_bound(b, e, key);		// =(1)

	if (lb != e && *lb == key)				// *(1) != (1) ==(1)
		return lb;							// v(1)
	return e;
}
// v(3) &(1) =(1) *(1) != (1) ==(1)
template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T & key) // v(2)  &(1)
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

template<class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T & key)
{
	assert(std::is_sorted(b, e));
	while (b < e)						//O(1) * log n
	{
		TIter m = b + (e - b) / 2;
		// [b, m) U [m] U [m+1, e)
		if (key < *m)
			e = m;
		else
			b = m + 1;
	}

	return b;
}

template<class TIter, class T>
size_t count_7(TIter b, TIter e) // O(1)
{
	return						// O(1)
		upper_bound(b, e, 7) - // O(log n) , n=e-b
		lower_bound(b, e, 7);  // O(log n)
}

template<class TIter>
void iter_swap(TIter i, TIter j)
{
	TIter = j;
	j = i;
	i = tmp;
}

template<class TIter>
void bubble_sort(TIter b, TIter e)
{
	for (TIter i = b; i < e; ++i)
	{
		// [unsorted) [sorted)
		// [b, i)     [i, e)
		assert(is_sorted(i, e));
		for (TIter j = b; j < i; ++j)  // [b, i)
		{
			// [b, j) [j, i)
			auto next = j + 1;
			if (*next < *j)
				iter_swap(j, next);
		}
		assert(is_sorted(i, e));
	}
}
 
int* my_lower_bound(int* b, int* e, const int & key)
{
	//assert(b < = e && std::is_sorted(b));
	assert(e-b >= 0);
	while (b < e)
	{
		
	}
	return b;
}
int* my_upper_bound(int* b, int* e, const int & key)
{
	return b;
}
size_t count_7(int* b, int* e)
{
	return my_upper_bound(b, e, 7) - my_lower_bound(b, e, 7);
}

size_t remove_even(int * b, int * e, int value)
{
	assert(e - b >= 0);

	while (b < e)
	{
		if (*b == value)
		{
			cout << *b << " :: ";
			int * tmp = b;		
			b = b + 1;
			delete tmp;
			tmp = NULL;
			cout << *b << endl;
		}
		else
			++b;
	}

	return e - b;
}


void sort_pair(int * b, int * e)
{
	for (int *i = b; i < e; ++i)
	{
		//iter_swap(i, min_search(i, e));
		//assert(is_sorted(b, i));
		for (int * j = i + 1; j < e; ++j)
		{
			//assert(i < j);
			if (*j < *i)
			{
				cout << "less\n";
				int *tmp = j;
				j = i;
				i = tmp;
			}
		}	
	}

	while (b != e)
	{
		cout << *b << " ";
		++b;
	}
	cout << endl;
}
