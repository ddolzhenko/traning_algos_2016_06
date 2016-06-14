#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int search_1(int arr[], size_t size, int key);
int search_2(int arr[], size_t size, int key);
int search_3(int arr[], size_t size, int key);
int search_4(int arr[], size_t size, int key);

template <class TExpect, class TFunc, class TParam1, class TParam2, class TParam3>
void test(TExpect expected, TFunc func, TParam1 param1, TParam2 param2, TParam3 param3)
{
	auto result = func(param1, param2, param3);
	cout << "Testing " << expected << "==" << "func(" << param1 << ", " << param2 ", " << param3 << ")" << endl;
	cout << string(80, '-') << endl << (expected != result) ? "fail" : "OK" << endl;
}

template<class TFunc>
void testSearchGeneral(TFunc search_func)
{
	int key;

	auto search_1 = [=](std::vector<int> v, int  key)
	{
		return search_func(&v[0], v.size(), key);
	};
	typedef std::vector<int> v;
	//key is not in array
	//degenerated
	test(-1, search_1, v({}), key);

	//trivial
	test(-1, search_1, v({1, 1}), key);
	test(-1, search_1, v({1, 2}), key);
	test(-1, search_1, v({2, 1}), key);

	//normal
	test(-1, search_1, v({ 1, 1, 4, 6, 7 }), key);
	test(-1, search_1, v({ 1, 1, 7, , 45, 12, 78 }), key);

	//key in array
	//trivial
	test(0, search_1, v({key}), key);
	//trivial2
	test(1, search_1, v({1,key}), key);
	test(0, search_1, v({key, 2}), key);
	test(0, search_1, v({key, key}), key);

	//normal
	test(0, search_1, v({ key, 1, 4, 6, 9, 23, 56 }), key);
	test(5, search_1, v({ 1, 4, 6, 9, 23, 56, key }), key);
	test(3, search_1, v({ 1, 4, 6, key, 9, 23, 56 }), key);
}

ostream& operator << (ostream& o, const vector<int> & data)
{
	o << "{";
	for (const auto& x : data) o << x << ", ";
	return o;
}

void testSearch()
{
	testSearchGeneral(search_1);
}

int main()
{

	testSearch();
	return 0;
}

int search_1(int arr[], size_t size, int key)
{
	assert(arr != 0);

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == key) return i;
	}
	return -1;
}

int search_2(int arr[], size_t size, int key)
{
	assert(arr != 0);

	size_t i = 0;
	while (i < size)
	{
		if (arr[i] == key) return i;
		i++;
	}
	return -1;
}

int search_3(int arr[], size_t size, int key)
{
	assert(arr != 0);

	arr[size] = key;
	size_t i = 0;
	while (arr[i] != key) i++;
	if (size != i) return i;
	else return -1;
}

int search_4(int arr[], size_t size, int key)
{
	assert(arr != 0);

	size_t last = size -1;
	int end = key;
	int save = arr[last];
	if (arr[last] == end) return last;
	else arr[last] = end;

	size_t i = 0;
	while (arr[i] != key) i++;
	arr[last] = save;
	if (last != i) return i;
	else return -1;
}
