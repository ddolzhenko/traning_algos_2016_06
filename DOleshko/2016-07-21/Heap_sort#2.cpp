

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

