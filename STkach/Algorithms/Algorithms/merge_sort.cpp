
template<class TIter>
void merge(TIter begin, TIter m, TIter end, TIter out)
{
	auto out_end = out_begin;
	auto
	auto mid = m;
	while ((begin < m) && (mid < end))
	{
		if (*begin < *mid)
		{
			*out = *begin;
			++out;
			++begin;
		}
		else
		{
			*out = *mid;
			++out;
			++mid;
		}
	}
}


template<class TIter>
void merge_sort(TIter begin, TIter end)
{
	if (end - begin > 1)
	{
		// [begin, end) = [begin, m) U [m, end)
		auto m = begin + (end - begin) / 2;
		merge_sort(begin, m);
		merge_sort(m, end);
		merge(begin, m, end);
	}
}

