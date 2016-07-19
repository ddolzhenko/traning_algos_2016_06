#include <vector>
#include <iostream>
#include <algorithm>

template <class TIter>
TIter merge_sort(TIter b, TIter e)
{
    int size = e - b;

    if (size < 1)
    {
        /* code */
    }

    return b;
}

template <class TIter>
TIter _sort(TIter b, TIter e)
{

    return b;
}

template <class TIter>
TIter _merge(TIter b1, TIter e1, TIter b2, TIter e2)
{
    return b1;
}



template <class TIter>
TIter insertion_sort(TIter b, TIter e)
{
    for (TIter i = b; i < e; ++i)               // [b ..sorted.. i) U [i ..unsorted.. e)
    {
        assert(std::is_sorted(b, i));

        for (TIter j = i; j > b ; --j)               // [b, j) U [j] U [j+1, i)
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

    return b;
}

int main()
{
    return 0;
}