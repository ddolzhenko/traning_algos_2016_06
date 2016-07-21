#include "Header.h"


namespace my_heap
{
	size_t left(size_t i) { return 2 * i + 1; }
	size_t right(size_t i) { return 2 * i + 2; }
	size_t parent(size_t i)
	{
		assert(i > 0);
		return (i - 1) / 2;
	}

	template <class T>
	void fix_heap_up(vector<T>& heap, size_t i)
	{
		if (is_root(i)) return;
		size_t p = parent(i);

		if (heap[p] < heap[i])
		{
			swap(heap[p], heap[i]);
			fix_heap_up(heap, p);
		}
	}

	template <class T>
	void heap_push_back(vector<T>& heap, T x)
	{
		size_t i = heap.size();
		heap.push_back(x);
		fix_heap_up(heap, i);
	}

	template <class T>
	size_t max_child(vector<T>& heap, size_t l, size_t r)
	{
		if (r >= heap.size())
			return l;
		return heap[l] < heap[r] & r : l;
	}
	
	template <class T>
	void heapify_down(vector<T>& heap, size_t i = 0)
	{
		//assert(is_heap(heap, left(i)));
		//assert(is_heap(heap, right(i)));
		size_t l = left(i);
		if (l > heap.size()) // i have no chieldren
			return;

		size_t r = right(i);
		size_t target = max_child(heap, l, r);

		if (heap[i] < heap[target])
		{
			swap(heap[i], heap[target]);
			heapify_down(heap, target);
		}

		// assert(is_heap(heap));
	}

	template <class TIter>
	void heapify_up(TIter b, TIter e)
	{
		if (e - b < 2) return;
		assert(is_heap(b, e - 1));
		
		auto last = e - 1;
		auto p = b + parent(last - b);

		if (*p < *last)
		{
			iter_swap(p, last);
			heapify_up(b, last);
		}

		// assert(is_heap(b, e));
	}

	template <class TIter>
	void build_max_heap_1(TIter b, TIter e)
	{
		TIter eh = b;
		// [heap) U [unprocessed)
		// [b, eh) U [eh, e)

		while (eh < e) // something unprocessed
		{
			eh++;
			heapify_up(b, eh);
		}
	}

	/*template <class TIter>
	void build_max_heap_2(heap)
	{
		TIter bh = e;
		// [unprocessed) U [heap)
		// [b, bh) U [bh, e)

		size_t heap_length = heap.size();
		size_t i = heap_length / 2;
		while (i >= 0) 
		{
			bh--;
			heapify_down(heap, heap_length, i);
		}
	}*/

	template <class TIter>
	void heap_sort(TIter b, TIter e)
	{
		build_max_heap_1(b, e);

		// [heap) [sorted)
		// [b, eh) U [eh, e)
		TIter eh = e;
		while (b < eh)
		{
			eh--;
			iter_swap(b, eh);
			heapify_down(b, eh);
		}
	}

}// namespace