#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>

void swap(int* arr, int i, int j)
{
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}
template<class TIter>
void bruteforceSort(TIter b, TIter e) 
{
	for(TIter i = b; i < e; i++)
	{
		assert(std::is_sorted(b, i));
		for(TIter j = i+1; j < e; j++)
		{
			if (*j < *i)
			{
				std::iter_swap(arr, i, j);
			}
		}
	}
}

template<class TIter>
void selectionSort(TIter b, TIter e) 
{
	for(TIter i = b; i < e; i++)
	{
		assert(std::is_sorted(b, i));
		std::iter_swap(i, min_element(i,e));
	}
}

template<class TIter>
void bubbleSort(TIter b, TIter e) 
{
	for(TIter i = e; i != b; i--)
	{
		// [b, i)   [i, e)
		assert(std::is_sorted(i, e));

		for(TIter j = b+1; j < i; ++j)
		{
			// [b, j)  [j, i)
			assert(j == max_element(b, j));

			auto prev = j - 1;
			if(*j < *prev)
				std::iter_swap(j, prev);

			assert(j == max_element(b, j));
		}

		assert(std::is_sorted(i, e));
		
	}
}

template<class TIter>
void insertionSort(TIter b, TIter e) 
{
	// [sorted) [unsorted)
	for (TIter i = b; i < e; i++)
	{
		assert(is_sorted(b, i));

		for (TIter j = i; j > b; j--)
		{
			// [b, j) [j] [j+1, i + 1)
			assert(is_sorted(b, j));
			assert(is_sorted(j, i));

			auto prev = j - 1;
			if (*j < *prev)
				iter_swap(j, prev);
			else
				break;
		}

		assert(is_sorted(b, i));
	}
}

int main()
{
    int A[] = {11,2,3};
    bruteforceSort(A, 3);
    for (int i = 0; i < 3; i++) std::cout<<" "<<A[i];
    return 0;
}