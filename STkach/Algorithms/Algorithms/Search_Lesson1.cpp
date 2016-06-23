#include <cassert>

int search_1(int m[], int size, int key);
int search_2(int m[], int size, int key);
int search_3(int m[], int size, int key);
int search_4(int m[], int size, int key);

int search_1(int m[], int size, int key)
{
	//assert(m != 0);
	assert(size >= 0);

	for (int i = 0; i < size; ++i)
	{
		if (m[i] == key)
			return i;
	}
	return -1;
}

int search_2(int m[], int size, int key)
{
	int i = 0;
	while (i < size)
	{
		if (m[i] == key)
			return i;

		++i;
	}
	return -1;
}

int search_3(int m[], int size, int key)
{
	m[size] = key;
	int i = 0;

	while (m[i] != key)
	{
		++i;
	}

	if (size == i)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

int search_4(int m[], int size, int key)
{
	int end = key;
	int last = size - 1;
	int original_end = m[last];

	if (m[last] != end)
	{
		m[last] = end;
	}
	else
	{
		return last;
	}

	int i = 0;
	while (m[i] != key)
	{
		++i;
	}

	m[last] = original_end;

	if (last == i)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

 
int binary_search_recursive(int A[], int size, int key)
{ 
	//[A, (a+size))
	if (size == 0)
	{
		return -1;
	}

	int m = size / 2;
	if (key < A[m])
	{
		return binary_search_recursive(A, m, key);
	}
	else if(A[m] < key)
	{
		return m + 1 + binary_search_recursive(A + m + 1, size - m - 1, key);

	}
	else
	{
		return m;
	}
}

int binary_search(int A[], int size, int key)
{
	assert(size >= 0);
	//assert(std::is_sorted(A, A + size));

	while (size != 0)				//  1
	{
		//[0, m)[m][m+1, size)
		int m = size / 2;			//  1, +1 /
		if (key < A[m])				//  1 <
			size = m;				//  1
		else if (A[m] < key)		//
		{
			A = A + m + 1;
			size -= m + 1;
		}
		else
			return m;
	}
	return -1;
}

template<class TIter, class T>
TIter binary_search(TIter b, TIter e, const T& key)
{
	assert(std::is_sorted(b, e));
	auto end = e;
	while (b < e)
	{
		TIter m = b + (e - b) / 2;
		if (key < *m)
		{
			e = m;
		}
		else if(*m < key)
		{
			b = m + 1;
		}
		else
		{
			return m;
		}
	}
}

//lower_bound()

template<class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T& key)
{
	while (b < e)
	{
		TIter m = b + (e - b) / 2;	// 4
		//[b, m)U [m] U [m+1, e)
		if (*m < key)				// 1
		{
			b = m + 1; // m+1, e	// 2
		}
		else
		{
			e = m; //[b, m)			// 1
		}
	}
	return b;
}

template<class TIter, class T>
TIter binary_search2(TIter b, TIter e, const T& key) // O(log n)
{
	auto lb = lower_bound(b, e, key);	// log n

	if (lb != e && *lb == key)			// O(1)
		return lb;
	return e;
}

template <class TIter>
size_t count_7(TIter b, TIter e)		// O(1)
{
	return upper_bound(b, e) - lower_bound(b, e);	// O(1) + O(log n) + O(log n)
}

template<class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T& key)	// O(1)
{
	while (b < e)						// o(1) * log n
	{
		TIter m = b + (e - b) / 2;		//O(1)
		//[b, m)U [m] U [m+1, e)
		if (key < *m)
		{
			e = m;
		}
		else
		{
			b = m + 1;
		}
	}
	return b;
}