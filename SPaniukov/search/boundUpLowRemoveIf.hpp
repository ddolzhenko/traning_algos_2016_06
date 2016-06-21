#ifndef boundUpLowRemoveIf_hpp
#define boundUpLowRemoveIf_hpp
#include <cassert>

template<class TIter, class T>	
TIter lowerBound(TIter begin, TIter end, const T& key)
{
	assert(std::is_sorted(begin, end));

	while (begin < end)
	{
		TIter middle = begin + (begin - end) / 2;
		// [begin, middle) and [middle] and (middle, end)
		if (*middle < key) begin = middle + 1; //[middle] and (middle, end)
		else end = middle;// [begin, middle)
	}
	return end;
}

template<class TIter, class T>
TIter upperBound(TIter begin, TIter end, const T& key)
{
	assert(std::is_sorted(begin, end));

	while (begin < end)
	{
		TIter middle = begin + (begin - end) / 2;
		// [begin, middle) and [middle] and (middle, end)
		if (key < *middle) end = middle; // [begin, middle)
		else begin = middle+1;//[middle] and (middle, end)
	}
	return begin;
}

template<class TIter, class T>
TIter remove_even(TIter begin, TIter end)
{
	TIter temp = end;
	while (begin < temp)
	{
		//[begin, even) and [even] and (even, end)
		if ((*begin) / 2)
		{
			end = begin + 1;
		}
		else
		{

		}
		begin++;
	}
	return end;
}
#endif
