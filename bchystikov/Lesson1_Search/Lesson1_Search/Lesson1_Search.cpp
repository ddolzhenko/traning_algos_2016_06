#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

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

//Tests!!!
template<class TExpected, class TFunc, class TParam1, class TPatam2>
void test(TExpected expected, TFunc f, TParam1 param1, TPatam2 param2)
{
	auto result = f(param1, param2);
	cout << "testing: " << expected << "== f(" << param1 << "," << param2 << ")\n";
	if (expected == result)
	{
		cout << string(80, '-') << (expected != result ? "fail" : "ok") << endl;
	}
}

ostream & operator<<(ostream & o, const vector<int>& data)
{
	o << "{";
	for (const auto & x : data)
		o << x << ", ";
	return o << "}";
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
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
	test(-1, search_func, Vec(), key);

	//trivial
	test(-1, search_func, Vec({ 1 }), key);

	//trivial 2
	test(-1, search_func, Vec( { 1, 1 }), key);
	test(-1, search_func, Vec( { 1, 2 }), key);
	test(-1, search_func, Vec( { 2, 1 }), key);

	//normal
	test(-1, search_func, Vec({ 2, 1, 43, 45, 425, 23 }), key);
	test(-1, search_func, Vec({ 2, 1, 43, 45, 425, 23 , -900 }), key);

	//key not in array
	//trivial
	test(0, search_func, Vec({ key }), key);

	//trivial 2
	test(1, search_func, Vec({ 1, key }), key);
	test(0, search_func, Vec({ key, 2 }), key);
	test(0, search_func, Vec({ key, key }), key);

	//normal
	test(0, search_func, Vec({ key, 1, 43, 45, 425, 23 }), key);
	test(2, search_func, Vec({ 2, 1, key, 45, 425, 23 , -900 }), key);
	test(6, search_func, Vec({ 2, 1, 43, 45, 425, 23 , key }), key);
}

void test_search()
{
   test_search_general(search1);
   //test_search_general(search2);
   test_search_general(search3);
}


int main()
{
	test_search();
	system("pause");
	return 0;
}

