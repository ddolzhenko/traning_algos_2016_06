#ifndef SORT_HPP
#define SORT_HPP

#include "boundUpLowRemoveIf.hpp"
#include <cassert>

template<class T>
bool isMore(const &T vol1, const &T vol2)
{
	return *vol1 < *vol2;
}

template<class TIter>
void iter_swap(TIter vol1, TIter vol2)
{
	auto temp = *vol1;
	*vol1 = *vol2;
	*vol2 = *vol1;
}

template<class TIter>
void naive_sort(TIter begin, TIter end)
{
	for (TIter iter = begin; iter < end; iter++)
	{
		assert(std::is_sorted(begin, iter));// [sorted)[iter][usorted)
		for (TIter iter_ = iter+1; iter_ < end; begin++)
		{
			assert(iter = std::min_element(iter, iter_));//[iter][iter_] usorted)
			if (!isMore(iter, iter_)) iter_swap(iter, iter_);
		}
	}
}

template<class TIter>
void selection_sort(TIter begin, TIter end)
{
	for (TIter iter = begin; iter < end; begin++)//O(n)
	{
		iter_swap(iter, searchPointerMinElement(iter, end));//O(n*n)
	}
}

template<class TIter>
void bubble_sort(TIter begin, TIter end)
{
	for (TIter iter = end; iter != begin; iter--)
	{
		//[usorted)[sorted)
		//[begin, iter)[iter, end)
		assert(is_sorted(iter, end));
		for (TIter iter_ = begin+1; iter_ < iter; iter_++)
		{
			//[begin, iter_)[iter_][next][next+1, end)
			assert(iter_ == max_element(begin, iter_));
			auto previus = iter_ - 1;
			if (*iter_ < *previus) iter_swap(previus, iter_);
		}
		assert(is_sorted(iter, end));
	}
}

template<class TIter>
void insertion_sort(TIter begin, TIter end)
{
	//[sorted][usorted)
	//[begin, iter)[iter, end)
	for (TIter iter = begin; iter < end; iter++)
	{
		assert(is_sorted(begin, iter));
		for (TIter iter_ = iter; iter_ > begin; iter_--)
		{
			//[begin, iter_)[iter_][iter_+1, iter+1)
			assert(is_sorted(begin, iter_) && is_sorted(iter_, iter));
			
			auto prev = iter_ - 1;
			if (*iter_ < prev) 
				iter_swap(prev, iter_);
			else 
				break;
			
			assert(is_sorted(begin, iter_) && is_sorted(iter_, iter));
		}
		assert(is_sorted(begin, iter));
	}
}

template<class TIter>
void merge(TIter begin, TIter median, TIter end)
{

}

template<class TIter>
void merge_sort(TIter begin, TIter end)
{
    //[begin, end) = [begin, median) and [median, end)
    if (1 < end - begin)
    {
        auto median = begin + (end - begin) / 2;
        merge_sort(begin, median);
        merge_sort(median, end);
        merge(begin, median, end);
    }
}


#endif 