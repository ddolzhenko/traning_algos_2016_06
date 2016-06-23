#ifndef boundUpLowRemoveIf_hpp
#define boundUpLowRemoveIf_hpp
#include <cassert>
#include <iostream>

template<class TIter, class T>	
TIter lowerBound(TIter begin, TIter end, const T& key)
{
	assert(std::is_sorted(begin, end));

	while (begin < end)//<1
	{
		TIter middle = begin + (begin - end) / 2;//4
		// [begin, middle) and [middle] and (middle, end)
		if (*middle < key) begin = middle + 1; //[middle] and (middle, end)//log4n
		else end = middle;// [begin, middle)
	}
	return end;//1
}

template<class TIter, class T>
TIter upperBound(TIter begin, TIter end, const T& key)          //O(1)
{
	assert(std::is_sorted(begin, end));

	while (begin < end)                                         //O(log n)
	{
		TIter middle = begin + (begin - end) / 2;               //O(1)
		// [begin, middle) and [middle] and (middle, end)       //O(1)
		if (key < *middle) end = middle; // [begin, middle)     //O(1)
		else begin = middle+1;//[middle] and (middle, end)      //O(1)
	}
	return begin;                                               //O(1)
}

template <class TIter, class T>
TIter binary_search(TIter begin, TIter end, const T& key) {//= 3
   auto lb = lowerBound(begin, end, key);//=4+log4n+6
   TIter iter = end;//1
   if (lb != end && *lb == key) iter = lb;//4
   return iter;//1
}//complexity log4n+18


template <class TIter>
size_t count_7(TIter b, Titer e)//O(1)
{
   return upperBound(b, e, 7) - lowerBound(b, e, 7);//O(1)+O(log n) + O(log n)== O(log n)
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
//test
#endif
