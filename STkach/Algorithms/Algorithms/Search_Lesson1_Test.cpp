#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <vector>

#include "Search_Lesson1.cpp"

using namespace std;

template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
	auto result = f(param1, param2);

	cout << "testing: " << expected << "==" << "f(" << param1 << ", " << param2 << ")" << endl;
	cout << string(80, '-') << endl << (expected != result ? "fail" : "ok") << endl;

	if (expected != result)
	{
		cout << "fail";
	}
}

template <class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key) {
		if (v.size() == 0)
			return base_search_func(0, v.size(), key);
		return base_search_func(&v[0], v.size(), key);
	};

	int key = 42;
	
	// key not in array
	typedef std::vector<int> Vec;
		// degenerated
	    test(-1, search_func, Vec(), key);
		// trivial
		test(-1, search_func, Vec({ 1 }), key);
		// trivial2nd
		test(-1, search_func, Vec({1, 1}), key);
		test(-1, search_func, Vec({1, 2}), key);
		test(-1, search_func, Vec({2, 1}), key);

		// normal
		test(-1, search_func, Vec({1, 1, 4, 56, 23}), key);
		test(-1, search_func, Vec({1, 1, 4, 56, 23, 46}), key);

	//key in array
		// trivial
		test(0, search_func, Vec({ key }), key);

		// trivial2nd
		test(1, search_func, Vec({ 1, key }), key);
		//test(0, search_func, Vec({ key, 2 }), key);
		//test(0, search_func, Vec({ key, key }), key);

		// normal
		test(0, search_func, Vec({ key, 1, 1, 4, 56, 23 }), key);
		test(6, search_func, Vec({ 1, 1, 1, 4, 12, 23, key }), key);
		test(4, search_func, Vec({ 1, 1, 1, 4, key, 56, 58 }), key);
		
		test(8, search_func, Vec({ 2, 4, 5, 6, 11, 14, 15, 20, 42 }), key);
}

void test_search()
{
	test_search_general(binary_search);
}

ostream& operator<<(ostream& o, const vector<int>& data)
{
	o << "{";
	for (const auto& x : data)
		o << x << ", ";
	return o << "}";
}
