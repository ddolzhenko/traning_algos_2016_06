
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
    if (0 == M || size <= 0)
    {
        return -1;
    }

    int sizeLeft = size / 2;
    int binIndex = sizeLeft;

    while ( sizeLeft > 0 ) 
    {
        sizeLeft = sizeLeft / 2;

        if (key == M[binIndex]) 
        {
            return binIndex;
        } 
        else if (key > M[binIndex]) 
        {
            sizeLeft > 0 ? binIndex += sizeLeft : ++binIndex;
        }
        else
        {
            binIndex = sizeLeft;
        }
    }

    if (key == M[binIndex])
    {
    	return binIndex;
    }
    else
    {
    	return -1;
    }
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
	std::cout << std::string(40, '-') << (expected != result ? "FAIL\n" : "OK\n");
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
	auto search_func = [=](std::vector<int> v, int key)
	{
		//return base_search_func(&v[0], v.size(), key);
		if(v.size() == 0)
		{
          return base_search_func(0, v.size(), key);
		}
		else
		{
			return base_search_func(&v[0], v.size(), key);
		}
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
		test(1, search_func, Vec({-87, key}), key);

		//normal
		test(1, search_func, Vec({100, key, 6, -42}), key);
}

template<class TFunc>
void test_search_binary(TFunc base_search_func)
{
    auto search_func = [=](std::vector<int> v, int key)
    {
        //return base_search_func(&v[0], v.size(), key);
        if(v.size() == 0)
        {
        	return base_search_func(0, 0, key);
        }
        else
        {
            return base_search_func(&v[0], v.size(), key);
        }
    };

    int key = 77;
    typedef std::vector<int> Vec;

    //key not in array
        //degenerated
        test(-1, search_func, std::vector<int>(), key);

        //trivial
        test(-1, search_func, Vec({1}), key);

        //normal
        test(-1, search_func, Vec({-80, 95, 106, 142}), key);

    //key not in array
        //trivial
        test(0, search_func, Vec({key}), key);
        test(1, search_func, Vec({-87, key}), key);

        //normal
        test(0, search_func, Vec({key, 80, 86, 92}), key);
        test(2, search_func, Vec({10, 35, key, 86, 92}), key);
        test(4, search_func, Vec({10, 35, 56, 72, key}), key);
}

void test_search()
{
	//test_search_general(search_1);
    test_search_binary(binarySearch);
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

	return 0;
}


