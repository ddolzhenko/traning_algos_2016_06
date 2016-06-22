#ifndef boundUpLowRemoveIf_hpp
#define boundUpLowRemoveIf_hpp
#include <cassert>
#include <iostream>

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

template<class TIter>
bool isEven(TIter iter)
{
   return !((*iter) % 2);
}

template<class TIter>
TIter remove_even(TIter begin, TIter end)
{
   assert(begin < end);

   auto temp = begin;
	while (begin < end)
	{
		//[begin, even) and [even] and (even, end)
		if (!isEven(begin))//[begin, even) and [even]
		{
         *temp = *begin;
         temp++;
      }
      begin++; //(even, end)
	}
	return temp;
}

template<class TIter, class TFunc>
TIter remove_if(TIter begin, TIter end, TFunc predicat)
{
   assert(begin < end);

   auto temp = begin;
   while (begin < end)
   {
      //[begin, even) and [even] and (even, end)
      if (!predicat(begin))//[begin, even) and [even]
      {
         *temp = *begin;
         temp++;
      }
      begin++; //(even, end)
   }
   return temp;
}

#endif
