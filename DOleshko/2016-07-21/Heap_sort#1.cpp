
namespace HeapSort
{
    size_t left(size_t i)   { return 2*i+1; }
    size_t right(size_t i)  { return 2*i+2; }
    size_t parent(size_t i) 
    {
        assert(i > 0); 
        return (i-1)/2; 
    }
    bool is_root(size_t i)  { return i == 0; }

    template <class T>
    void fix_heap_up(std::vector<T>& heap, size_t i) //heapify_up
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
    void heap_push_back(std::vector<T>& heap, T x) 
    {
        size_t i = heap.size();
        heap.push_back(x);
        fix_heap_up(heap, i);
    }

    /////////////////

    template <class T>
    void heapify_down_dd(std::vector<T>& heap, size_t i = 0 /* root*/) O(log n)
    {
        size_t l = left(i);
        if (l > heap.size())  return; // there are no leaves

        size_t r = right(i);

        size_t swap_index = max_node(l, r, heap);

        if (heap[i] < heap[target])
        {
            swap(heap[i], heap[target]);
            heapify_down_dd(heap, target);
        }
    }

    // 1 - max(A) == root(A) => 
    // 2 - push(x) => O(1){insert to vector} + O(heapify_up){log n} = O(log n)
    // 3 - pop(top) => O(log n) {swap TOP with LAST; erase LAST; heapify_up}

    template <class T>
    void heapify_down(std::vector<T>& heap, size_t i = 0 /* root*/)
    {
        size_t l = left(i);
        size_t r = right(i);

        bool r_exists = r > heap.size();

        if(r_exists && (heap[i] < heap[r]))
        {
            if (heap[r] < heap[l])
            {
                swap(heap[i], heap[l]);
                heapify_down(heap, l);
            }
            else
            {
                swap(heap[i], heap[r]);
                heapify_down(heap, r);
            }
        } 
        else if(heap[i] < heap[l])
        {
            swap(heap[i], heap[l]);
            heapify_down(heap, l);
        }

        return;
    }


} // namespace
