#ifndef ALGOS
#define ALGOS

#include <assert.h>
#include <algorithm>

namespace NAlgos
{
	void pointer_swap(int *i, int *j) {
		int tmp = *i;
		*i = *j;
		*j = tmp;
	}

	int *min_search(int *b, int *e)
	{
		int *min = b;
		while (++b < e)
		{
			if (*b < *min)
			{
				min = b;
			}
		}
		return min;
	}

	void selection_sort(int *b, int *e)
	{
		for (int *i = b; b < e; ++i)
		{
			// [sorted) [unsorted)
			// [b, i),  [i, e)
			assert(std::is_sorted(b, i));

			int *min_el = min_search(i, e);
			pointer_swap(i, min_el);

			assert(std::is_sorted(b, i));
		}

		assert(std::is_sorted(b, e));
	}

	void insertion_sort(int *b, int *e)
	{
		// [sorted) [unsorted)
		// [b, i)   [i, e)
		for (int *i = b; i < e; ++i)
		{
			assert(std::is_sorted(b, i));

			for (int *j = i; j > b; --j)
			{
				// [b, j) [j] [j + 1, i + 1)
				assert(std::is_sorted(b, j));
				assert(std::is_sorted(j, i));

				int *prev = j - 1;
				if (*j < *prev)
				{
					pointer_swap(j, prev);
				}
				else break;

				assert(std::is_sorted(b, j));
				assert(std::is_sorted(j, i));
			}

			assert(std::is_sorted(b, i));
		}
	}

}

#endif ALGOS

