#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <vector>
#include <assert>

using namespace std;

namespace NHeapSort 
{
	bool is_root(size_t i)
	{
		return i == 0;
	}

	size_t left(size_t i)
	{
		return 2 * i + 1;
	}

	size_t right(size_t i)
	{
		return 2 * i + 2;
	}

	size_t parent(size_t i)
	{
		return (i-1)/2;
	}

	template <class T>
	void fix_heap_up(vector<T>& heap, size_t i)
	{
		if (is_root(i)) return;
		
		size_t p = parent(i);
		if (heap[p]) < heap[i]) 
		{
			swap(heap[p], heap[i]);
			fix_heap_up(heap, p);
		}
	}

	size_t max_child(vector<T>& heap, size_t l, size_t r)
	{
		if (r >= heap.size()) return l;
		return heap[l] < heap[r] & r:l;
	}

	template <class TIter>
	void heapify_up(TIter bh, TIter eh)
	{
		if (eh - bh < 2) return;

		assert(is_heap(bh, eh - 1));

		auto last = eh - 1;
		auto p = bh + parent(last - bh);
		if (*p < *last)
		{
			iter_swap(p, last);
			heapify_up(bh, last);
		}
		assert(is_heap(bh, eh));
	}
}


template <class T>
void heap_push_back(vector<T>& heap, T x)
{
	size_t i = heap.size();
	heap.push_back(x);
	NHeapSort::fix_heap_up(heap, i);
}

template <class T>
void heapify_down(vector<T>& heap, size_t i)
{
	if (left(i) => heap.size())
	{
		return;
	}

	size_t temp = left(i);// max_child(heap, left(i), right(i))

	if (right(i) <= heap.size() && heap[left(i)] < heap[right(i)])
	{
		temp = right(i);
	}

	if (heap[i] < heap[temp])
	{
		swap(heap[i], heap[temp]);
		heapify_down(heap, heap[temp]);
	}
}

template <class TIter>
void buld_max_heap_v1(TIter b, TIter e)
{
	TIter bh = b;
	TIter eh = b;
	// [heap) U [unprocessed]
	// [bh, eh) U [eh, e)

	while (eh < e)
	{
		eh++;
		heapify_up(bh, eh);
	}
}

template <class TIter>
void buld_max_heap_v2(TIter b, TIter e)
{
	TIter bh = e;

	// [unprocessed) U [heap)
	// [b, bh) U [bh, e)
	auto heap_lenght = heap.size();
	auto index = heap_lenght / 2;
	while (index >= 0)
	{
		heapify_down(heap, heap_lenght, index);
	}
}

template <class TIter>
void heap_sort(TIter b, TIter e)
{
	buld_max_heap_v2(b, e);

	// [sorted) [heap)
	// [b, eh][eh, e)
	auto eh = e;
	while (b < eh)
	{
		eh--;
		iter_swap(b, eh);
		heapify_down(b, eh, b);
	}
}

#endif 
