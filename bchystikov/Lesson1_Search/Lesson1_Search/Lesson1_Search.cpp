#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;


int search1(int A[], int size, int key)
{
	//contract
	//assert(A != 0);
	assert(size >= 0);

	for (auto i = 0; i < size; ++i)
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
	if (size == 0)
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

	if (last_index != i)
		return i;

	return -1;

}

int * find_min_elem(int * b, int * e)
{
	int * result = b;
	for (; b < e; ++b)
	{
		if (*result > *b)
		{
			result = b;
		}
	}
	return result;
}

int binary_search_recurse(int A[], int size, int key)
{
	assert(size>=0);
	assert(is_sorted(A, A + size));
	//[A, A+size)

	if (size == 0)
	{
		return -1;
	}

	int m = size / 2;
	if (key < A[m])
	{
		return binary_search_recurse(A, m, key);
	}
	else if(A[m] < key)
	{
		int result = binary_search_recurse(A + m + 1, size - m - 1, key);
		result = result != -1 ? m + 1 + result : result;
		return result;
	}
	else
	{
		return m;
	}
}

int binary_search(int A[], int size, int key)
{
	assert(size>=0);
	assert(is_sorted(A, A + size));
	//[A, A+size)

	while (size != 0)
	{
		// [0, m)[m][m+1, size)
		int m = size / 2;
		if (key < A[m])
		{
			size = m;		//[0, m)
		}
		else if(A[m] < key)
		{
			A = A + m + 1;	//[m+1, size)
			size -= m + 1;
		}
		else
		{
			return m;
		}
	}
	return -1;
}

template <class TIter, class T>
TIter binary_search_new(TIter b, TIter e, T& key)
{
	assert(is_sorted(b, e));
	auto end = e;
	while (b < e)
	{
		TIter m = b + (e-b)/2;
		//[b, m) U [m] U [m+1, e)
		if (key < *m)
		{
			e = m;		//[b, m)
		}
		else if(key > *m)
		{
			b = m + 1;	//[m+1, e)
		}
		else
		{
			return m;
		}
	}
	return end;
}

template <class TIter, class T>
TIter lower_bound(TIter b, TIter e, T& key)
{
	assert(is_sorted(b, e));
	while (b < e)
	{
		TIter m = b + (e - b) / 2;
		// [b, m) U [m] U [m+1, e)
		if (*m < key) 
		{
			b = m+1;		//[m+1, e)
		}
		else
		{
			e = m;			//[b, m)
		}
	}
	return b;
}

template <class TIter, class T>
TIter upper_bound(TIter b, TIter e, T& key)
{
	assert(is_sorted(b, e));
	while (b < e)
	{
		TIter m = b + (e - b) / 2;
		// [b, m) U [m] U [m+1, e)
		if (*m < key)
		{
			e = m;			//[b, m)
		}
		else
		{
			b = m + 1;		//[m+1, e)
		}
	}
	return b;
}

template <class TIter>
size_t count_7(TIter b, TIter e)
{
	return upper_bound(b, e) - lower_bound(b, e);
}



template <class TIter, class T>
TIter lbinary_search(TIter b, TIter e, T& key)
{
	//HW: remove "==" && "!="
	auto lb = lower_bound(b, e, key);
	if(lb != e && *lb == key)
		return lb;
	return e;
}

bool isOdd(int num)
{
	return num % 2 == 0;
}

template <class TIter>
TIter remove_if_my(TIter b, TIter e)
{
	for (auto it = b; it < e;)
	{
		auto next_it = it+1;
		if(isOdd(*it) && next_it != e)
		{
			it = next_it;
			--e;
		}
		else
		{
			++it;
		}
	}
	return e;
}


//Tests!!!
template<class TExpected, class TFunc, class TParam1, class TPatam2>
void test(TExpected expected, TFunc f, TParam1 param1, TPatam2 param2)
{
	auto result = f(param1, param2);
	cout << "testing: " << expected << "== f(" << param1 << "," << param2 << ")\n";
	//if (expected == result)
	//{
		cout << string(80, '-') << (expected != result ? "fail" : "ok") << endl;
	//}
}

ostream & operator<<(ostream & o, const vector<int>& data)
{
	o << "{ ";
	for (const auto & x : data)
		o << x << " ";
	return o << "}";
}

template<class TFunc>
void test_search_general(TFunc base_search_func, string description)
{
   cout << description << ":\n";
	auto search_func = [=](vector<int> v, int key)
	{
		if(v.size() == 0)
			return base_search_func(0, v.size(), key);//!!!!!!!!!!!!!!!!!!!!!!
		return base_search_func(&v[0], v.size(), key);
	};

	typedef vector<int> Vec;
	int key = 42;
	//key not in array
	//degenerated
	//test(-1, search_func, Vec(), key);

	//trivial
	test(-1, search_func, Vec({ 1 }), key);

	//trivial 2
	test(-1, search_func, Vec( { 1, 1 }), key);
	test(-1, search_func, Vec( { 1, 2 }), key);
	//test(-1, search_func, Vec( { 2, 1 }), key);

	//normal
	test(-1, search_func, Vec({ 1, 2, 43, 45, 425 }), key);
	test(-1, search_func, Vec({ 1, 2, 43, 45, 425 }), key);

	//key not in array
	//trivial
	test(0, search_func, Vec({ key }), key);

	//trivial 2
	test(1, search_func, Vec({ 1, key }), key);
	//test(0, search_func, Vec({ key, 2 }), key);
   test(1, search_func, Vec({ key, key }), key);
   //test(0, search_func, Vec({ key, key }), key);//!!!!

	//normal
	//test(0, search_func, Vec({ key, 1, 43, 45, 425, 23 }), key);
	test(3, search_func, Vec({ -900, 1, 2, key, 45, 425 }), key);
	//test(6, search_func, Vec({ 2, 1, 43, 45, 425, 23 , key }), key);
}

void test_search()
{
	test_search_general(search1, "SEARCH1");
   //test_search_general(search2, "search2");
	test_search_general(search3, "SEARCH3");
	test_search_general(binary_search_recurse, "BINARY_SEARCH_RECURSE");
	test_search_general(binary_search, "BINARY_SEARCH");
}

int main()
{
	//test_search();

	typedef vector<int> Vec;
	Vec v1 = { };
	Vec v2 = { 1 };
	Vec v3 = { 2 };
	Vec v4 = { 1, 2, 3, 4 };

	int a[] = { 1, 2, 3, 4, 5 };
	//int b[] = { 5 };
	//cout << *find_min_elem(a, a + 3) << endl;
	//cout << *find_min_elem(b, b + 1) << endl;
	remove_if_my(a, a+5);

	for (int i = 0; i < 5; ++i)
	{
		cout << a[i] << endl;
	}


	//remove_if_my(v1);
	//remove_if_my(v2);
	//remove_if_my(v3);
	//remove_if_my(v4);

	//cout << v1 << endl;
	//cout << v2 << endl;
	//cout << v3 << endl;
	//cout << v4 << endl;

	system("pause");
	return 0;
}

