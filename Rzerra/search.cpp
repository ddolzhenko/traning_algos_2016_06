//#include <iostream>
//#include <iomanip>
//#include <cassert>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//int search1(int iArray[], int iSize, int iKey)
//{
////	assert(iArray!=0);
//	assert(iSize>=0);
//
//	for(int i=0; i<iSize; ++i)
//	{
//		if(iArray[i]==iKey)
//			return i;
//	}
//	return -1;
//}
//
//int search2(int iArray[], int iSize, int iKey)
//{
////	assert(iArray!=0);
//	assert(iSize>=0);
//
//	int i=0;
//	while(i<iSize)
//	{
//		if(iArray[i]==iKey)
//			return i;
//		++i;
//	}
//	return -1;
//}
//
//int search3(int iArray[], int iSize, int iKey)
//{
////	assert(iArray!=0);
//	assert(iSize>=0);
//
//	iArray[iSize] = iKey;
//	int i=0;
//	while(iArray[i]!=iKey)
//		++i;
//	if(i!=iSize)
//		return i;
//	return -1;
//}
//
//int search4(int iArray[], int iSize, int iKey)
//{
////	assert(iArray!=0);
//	assert(iSize>=0);
//
//	if(iSize==0)
//		return -1;
//
//	int end = iSize-1;
//	int last = iArray[end];
//	if(last==iKey)
//		return end;
//
//	int i=0;
//	while(iArray[i]!=iKey)
//		++i;
//	iArray[end] = last;
//	if(i!=iSize)
//		return i;
//	return -1;
//}
//
//template<class TExpect, class TFunc, class, class TParam1, class TParam2>
//void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
//{
//	auto result = f(param1, param2);
//
//	cout<<"testing "<<expected<<" == "<<"f("<<param1<<", "<<param2<<")\n";
//	cout<<string(80, '-')<<(expected!=result? "fail":"ok")<<endl;
//}
//
//std::ostream& operator<<(std::ostream& o, const std::vector<int>& data)
//{
//	o<<"{";
//	for(const auto& x: data) o<<x<<", ";
//	return o<<"}";
//}
//
//template<class TFunc>
//void test_search_general(TFunc base_search_func)
//{
//	auto search_func = [=](std::vector<int> v, int key)
//	{
//		if(v.size()==0)
//			return base_search_func(0, v.size(), key);
//		return base_search_func(&v[0], v.size(), key);
//	};
//	int key = 42;
//	typedef std::vector<int> fector;
//
//	// key not in array
//		// degenerated
//		test(-1, search_func, fector(), key);
//
//		// trivial
//		test(-1, search_func, fector({1}), key);
//
//		// second trivial
//		test(-1, search_func, fector({1, 1}), key);
//		test(-1, search_func, fector({1, 2}), key);
//		test(-1, search_func, fector({2, 1}), key);
//
//		// usual
//		test(-1, search_func, fector({1, 1, 4, 56, 23}), key);
//		test(-1, search_func, fector({1, 2, 43, 20, 5, 7}), key);
//
//	// key in array
//		// trivial
//		test(0, search_func, fector({key}), key);
//
//		// second trivial
//		test(1, search_func, fector({1, key}), key);
//		test(0, search_func, fector({key, 2}), key);
//		test(0, search_func, fector({key, key}), key);
//
//		// usual
//		test(0, search_func, fector({key, 1, 4, 56, 23}), key);
//		test(5, search_func, fector({1, 2, 43, 20, key}), key);
//		test(3, search_func, fector({8, 1, key, 56, key}), key);
//}
//
//void test_search()
//{
//	test_search_general(search1);
////	test_search_general(search2);
////	test_search_general(search3);
////	test_search_general(search4);
//}
//
//void main()
//{
//	test_search();
//}
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
	auto result = f(param1, param2);

	cout << "testing: " << expected << " == " << "f(" 
		<< param1 << ", " << param2 <<") = " << result << endl;
	cout << string(80, '-') 
		<< (expected != result ? "fail" : "ok") << endl;
}

ostream& operator<<(ostream& o, const std::vector<int>& data)
{
	o << "{";
	for(const auto& x : data)
		o << x << ", ";
	return o << "}";
}



int search_linear(int A[], int size, int key) {
	// assert(A != 0);
	assert(size >= 0);

	for(auto i = 0; i < size; ++i) {
		if(A[i] == key)
			return i;
	}

	return -1;
}


template<class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key) {
		if(v.size() == 0)
			return base_search_func(0, v.size(), key);
		return base_search_func(&v[0], v.size(), key);
	};

	int key = 42;

	// key not in array
	typedef std::vector<int> Vec;
	// degenerated:
	test(-1, search_func, Vec(), key);

	// trivial
	test(-1, search_func, Vec({1}), key);

	// trivial2nd
	test(-1, search_func, Vec({1, 1}), key);
	test(-1, search_func, Vec({1, 2}), key);
	test(-1, search_func, Vec({2, 1}), key);

	// normal
	test(-1, search_func, Vec({1, 1, 4, 56, 23}), key);
	test(-1, search_func, Vec({1, 1, 4, 56, 23, -100}), key);


	// key in array
	// trivial
	test(0, search_func, Vec({key}), key);

	// trivial2nd
	test(1, search_func, Vec({1, key}), key);
	test(0, search_func, Vec({key, 2}), key);
	test(0, search_func, Vec({key, key}), key);

	// normal
	test(0, search_func, Vec({key, 1, 1, 4, 56, 23}), key);
	test(5, search_func, Vec({1, 1, 4, 56, 23, key}), key);
	test(3, search_func, Vec({1, 1, 4, key, 56, 23}), key);
}


void test_search()
{


	test_search_general(search_linear);
}



int main() {
	test_search();
	return 0;
}