

template <class TIter>
TIter my_compare_all_sort(TIter b, TIter e)
{
    int size = e - b;

    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
           if (*(b+j) < *(b+i) )
            {
                std::swap(*(b+j), *(b+i))
            } 
        }
    }
}

/*
template <class TIter>
TIter min_element(TIter b, TIter e)
{
    if (first==last) 
        return last;
    ForwardIterator smallest = first;

    while (++first!=last)
        if (*first<*smallest)
            smallest=first;
    
    return smallest;
}
*/

template <class TIter>
TIter compare_all_sort(TIter b, TIter e)
{
    for (TIter i = b; i < e; ++i)               // [b ..sorted.. i) U [i ..unsorted.. e)
    {
        // assert (is_sorted(b, i))

        for (TIter j = i + 1; j < count; ++j)   // {[i] U} [i+1 .. .. j) U [j .. .. e)
        {
            assert(i < j); // assert (i == std::min_element(i, j))

            if (*j < *i)
            {
                std::iter_swap(i, j);
            }

            // assert (i == std::min_element(i, j))
        }
    }

    assert(std::is_sorted(b, e));
}

template <class TIter>
TIter selection_sort(TIter b, TIter e)
{
    for (TIter i = b; i < e; ++i)               // [b ..sorted.. i) U [i ..unsorted.. e)
    {
        assert (is_sorted(b, i))

        auto min = std::min_element(i, e);
        std::iter_swap(i, min);

        assert (is_sorted(b, i))
    }
}


template <class TIter>
TIter bubble_sort(TIter b, TIter e)
{
    for (TIter i = e; i >= b; --i)               // [b ..unsorted.. i) U [i ..sorted.. e)
                                                 // any from [i ..sorted.. e) >= any from [b ..unsorted.. i)
    {
        assert(std::is_sorted(i, e));

        for (int j = b+1; j < i; ++j)             // [b, j) U [j, i)   
                                                  // [b, j-1) U [j-1] U [j] U [j+1, i)
        {
            assert( j == max_element(b, j))    // j - is always MAX that is going UPWORDS

            auto prev = j - 1;
            if (*prev < *j)
            {
                std::iter_swap(j, prev);
            }

            assert( j == max_element(b, j+1))
        }


        assert(std::is_sorted(i, e));
    }    
}

template <class TIter>
TIter insertion_sort(TIter b, TIter e)
{
    for (TIter i = b; i < e; ++i)               // [b ..sorted.. i) U [i ..unsorted.. e)
    {
        assert(std::is_sorted(b, i));

        for (int j = i; j > b ; --j)               // [b, j) U [j] U [j+1, i)
        {
            assert (std::is_sorted(b, j) && std::is_sorted(j, i));

            auto prev = j - 1;
            if (*j < *prev)
            {
                std::iter_swap(j, prev);
            }
            else
            {
                break;
            }
        }

        assert(std::is_sorted(b, i));
    }
}

int main()
{
    int A[] = {3, 5, 1, 8};
}