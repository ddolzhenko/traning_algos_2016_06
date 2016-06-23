#pragma once
#include <cassert>

using namespace std;

template <class TIter>
naive_sort(TIter begin, TIter end)
{
	for (TIter iter = begin; iter < end; ++iter)
	{
		assert(is_sorted(begin, iter))
		for (TIter iter2 = iter + 1; iter2 < end; ++iter)
		{
			assert(i == min_element(iter, iter2));
			if (*iter2 < iter)
			{
				iter_swap(iter, iter2);
			}
			assert(i == min_element(iter, iter2));
		}
		assert(is_sorted(begin, iter))

	}
	assert(is_sorted(begin, end))
}

template<class TIter>
TIter min_element(TIter begin, TIter end)
{
	while (begin < end)
	{
		
	}
}

template<class TIter>
void iter_swap(TIter first, TIter second)
{
	auto tmp = *first;

	*first = *second;
	*second = *tmp;

	
}

template<class TIter>
void selection_sort(TIter begin, TIter end)
{
	for (TIter iter = begin; iter < end; ++iter)
	{
		// [being, iter,) [iter, end)
		// [sorted) [unsorted)
		assert(is_sorted(begin, iter));
		iter_swap(iter, min_element(iter, end));
		assert(is_sorted(b, i));
	}
}

template <class TIter>
void bubble_sort(TIter begin, TIter end)
{
	for (TIter iter = end; iter >= begin; --iter)
	{
		// [unsorted) [sorted)
		// [begin, iter) [iter, begin)
		assert(is_sorted(iter, end));
		
		for (TIter iter2 = begin + 1; iter2 < iter; ++iter2)
		{
			// [begin, iter2 - 1) [iter2-1][iter][iter2+1, iter)
			assert(j == max_element(b, iter2))
			auto prev = iter2 - 1;
			if (*iter2 < *prev)
			{
				iter_swap(j, prev);
			}
			// assert(j == max_element(b, j))
		}
		assert(is_sorted(iter, end));
	}
}

template <class TIter>
void insertion_sort(TIter being, TIter end)
{
	
	for (TIter iter = begin; iter < end; ++iter)
	{
		//[sorted) [unsorted)
		//[begin, iter) [iter, end)
		assert(is_sorted(begin, iter));
		for (TIter iter2 = iter; iter2 > begin ; --iter2)
		{
			//[begin, iter2) [iter2] [iter2+1, end)
			assert(is_sorted(begin, iter2 && is_sorted(iter2, iter));
			auto prev = iter2 - 1;
			if (*iter2 < *prev)
			{
				iter_swap(iter2, prev);
			}
			else
				break;
			assert(is_sorted(begin, iter2 && is_sorted(iter2, iter));
		}
		assert(is_sorted(begin, iter));
	}
}