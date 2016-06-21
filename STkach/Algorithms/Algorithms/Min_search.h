#pragma once

int * min_search(int * begin, int * end)
{
	int * min = begin;

	while (begin < end)
	{
		if (*begin < *min)
		{
			min = begin;
		}
		++begin;
	}
	return min;
}