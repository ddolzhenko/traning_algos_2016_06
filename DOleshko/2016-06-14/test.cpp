
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

int search_1(int M[], int size, int key)
{
	//std::cout << "search_1 : key = " << key << std::endl;
	for(int i=0; i<size; ++i)
	{
		if(M[i] == key)
			return i;
	}

	return -1;
}

int search_2(int M[], int size, int key)
{
	//std::cout << "search_2 : key = " << key << std::endl;
	int i=0;
	M[size] = key;
	while(M[i] != key)
	{
		++i;
	}

	if(i != size)
	{
		return i;
	}

	return -1;
}

int search_3(int M[], int size, int key)
{
	//check function contract
	//assert(M != 0);
	assert(size >= 0); // replace int with size_t

	 //std::cout << "search_3 : key = " << key << std::endl;
	 if(M[size-1] == key)
	 {
	 	return size-1;
	 }
	
	int i = 0;
	int last = M[size-1];
	M[size-1] = key;

	while(M[i] != key)
	{
		++i;
	}

	M[size-1] = last;

	if(i != size-1)
	{
		return i;
	}

	return -1;
}

int binarySearch(int M[], int size, int key)
{
	return -1;
}

void printArr(int M[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << "[" << i << "]= " << M[i] << std::endl;
	}
}

template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc f, TParam1 param1, TParam2 param2)
{
	auto result = f(param1, param2);
	std::cout << "\ntesting: " << expected << " = " << "f (" << param1 << ", " << param2 << ")" << std::endl;
	std::cout << std::string(40, '-') << (expected != result ? "FAIL" : "OK");
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key)
	{
		return base_search_func(&v[0], v.size(), key);
	};

	int key = 77;
	typedef std::vector<int> Vec;

	//key not in array
		//degenerated
		test(-1, search_func, std::vector<int>(), key);

		//trivial
		test(-1, search_func, Vec({1}), key);

		//normal
		test(-1, search_func, Vec({100, 55, 6, -42}), key);

	//key not in array
		//trivial
		test(0, search_func, Vec({key}), key);

		//normal
		test(1, search_func, Vec({100, key, 6, -42}), key);
}
/*
int EMPTY [6];
int TRIVIAL [2] = {77};
int A [6] = {1,2,3,4,5,0};
int *nullPtr = 0;
*/
void test_search()
{
	test_search_general(search_1);
}

std::ostream& operator<<(std::ostream& o, const std::vector<int>& data)
{
	o << "{";
	for(const auto& x : data)
	{
		o << x << ", ";
	}

	return  o << "}";
}

int main (void)
{

	test_search();

	/*
	int i = 0;

	
	std::cout << "****************" << std::endl;
	printArr(A, 6);
	std::cout << search_1(A, 5, 4) << std::endl;
	std::cout << search_2(A, 5, 2) << std::endl;
	std::cout << search_2(EMPTY, 5, 7) << std::endl;
	std::cout << search_3(A, 5, 5) << std::endl;
	std::cout << search_3(A, 5, 7) << std::endl;
	std::cout << search_3(EMPTY, 6, 7) << std::endl;
	std::cout << search_3(TRIVIAL, 1, 7) << std::endl;
	std::cout << search_3(TRIVIAL, 1, 77) << std::endl;
	std::cout << search_3(nullPtr, 1, 77) << std::endl;

*/
	return 0;
}


