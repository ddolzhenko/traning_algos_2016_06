
template <class TIter>
void iter_swap(TIter i, TIter j) {
    auto tmp = *i;
    *i = *j;
    *j = tmp;
}


template <class TIter>
TIter min_element(TIter b, TIter e) {
    TIter result;
    while(b < e) {
        if(*b < *result)
            result = b;
        ++b;
    }

    return result;
}


template <class TIter>
void naive_sort(TIter b, TIter e) {

    for (TIter i = b; i < e; ++i) {
        assert(is_sorted(b, i));

        for (TIter j = i+1; j < e; ++j)
        {
            assert(i == min_element(i, j));
            
            if(*j < *i)
                iter_swap(i, j);

            assert(i == min_element(i, j));
        }
        assert(is_sorted(b, i));
    }
    assert(std::is_sorted(b, e));
}


template <class TIter>
void selection_sort(TIter b, TIter e) {
    // [b, i) [i e)
    // [sorted) [unsorted)
 
    for (TIter i = b; i < e; ++i) 
    {
        assert(is_sorted(b, i));
        iter_swap(i, min_element(i, e));
        assert(is_sorted(b, i));
    }

}

template <class TIter>
void selection_sort(TIter b, TIter e) {
    for (TIter i = b; i < e; ++i) 
        iter_swap(i, min_element(i, e));
}


template <class TIter>
void bubble_sort(TIter b, TIter e) {
    for (TIter i = e; i != b; --i) 
    {
        // [unsorted) [sorted)
        // [b, i)     [i, e)
        assert(is_sorted(i, e));
        assert(i == e || max_element(i, e) == i);

        for (TIter j = b+1; j < i; ++j)   // [b, i)
        {
            // [b, j-1)[j-1][j] [j+1  i)
            assert(j == max_element(b, j));
            
            auto prev = j-1;
            if(*j < *prev)
                iter_swap(j ,next);
            
            assert(j == max_element(b, j));
        }

        assert(is_sorted(i, e));
    }
}


template <class TIter>
void insertion_sort(TIter b, TIter e) {

    for(Titer i = b; i < e; ++i)
    {
        // [sorted) [unsorted)
        // [b, i)   [i, e)
        assert(is_sorted(b, i));

        for (Titer j = i; j > b; --j)
        {
            // [b, j)[j][j+1, i+1)
            assert(is_sorted(b, j) && is_sorted(j, i));
            auto prev = j-1;
            if(*j < *prev)
                iter_swap(j, prev);
            else
                break;

            assert(is_sorted(b, j) && is_sorted(j, i));
        }

        assert(is_sorted(b, i));
    }
}
  