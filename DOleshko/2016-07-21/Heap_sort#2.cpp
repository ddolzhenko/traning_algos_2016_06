

template <class TIter>
void heapify_up(TIter b, TIter e)
{
    if (e-b < 2) return;

    auto last = e - 1;
    auto p = b + HeapSort::parent(last - b);

    if (*p < *last)
    {
        iter_swap(p, last);
        heapify_up(b, last);
    }
}

template <class TIter>
void build_max_heap_1(TIter b, TIter e)
{
    // [HEAP) U [x] U (UNPROCESSED)
    TIter eh = b; //end of HEAP

    while(eh < e)
    {
        heapify_up(b, ++eh);
    }
}

template <class TIter>
void build_max_heap_2(heap) // TODO
{
    // [UNPROCESSED) U [HEAP)
    //TIter bh = e; //begin of HEAP

    heap_length = heap.size();
    inr i = heap_length / 2;  // half of ARRAY => leaves
    while(i > = 0)
    {
        heapify_down(heap, heap_length, i);
    }
}

template <class TIter>
void heap_sort(TIter b, TIter e) // O(n log n), but NOT CACHE FRIENDLY to much memory jumps
{
    build_max_heap(b, e);
    auto eh = e;

    //[b .. HEAP .. eh) U [SORTED)

    while(b < eh)
    {
        --eh;
        iter_swap(b, eh);
        heapify_down(b, eh, b);
    }
}
