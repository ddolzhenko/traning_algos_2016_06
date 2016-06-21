#pragma once

template <class TIter, class T>
TIter lower_bound(TIter begin, TIter end, T key)
{
	while (begin < end)
	{
		//[b, m)U [m] U [m+1, e)
		TIter m = begin + (end - begin) / 2;
		if (*m > key)
		{
			end = m;
		}
		else
		{
			begin = m + 1;
		}
	}
	return end;
}

template <class TIter, class T>
TIter upper_bound(TIter begin, TIter end, T key)
{
	while (begin < end)
	{
		TIter m = begin + (end - begin) / 2;
		if (key < *m)
		{
			end = m;
		}
		else
		{
			begin = m + 1;
		}
	}
	return begin;
}

template <class TIter>
TIter remove_even(TIter begin, TIter end)
{
	int count = 0;
	while (begin < end)
	{
		if (!(*begin / 2))
		{
			*begin = *(begin + 1);
			++count;
		}
		++begin;
	}
	return end - count;
}