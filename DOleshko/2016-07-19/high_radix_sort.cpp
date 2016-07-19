




template <class TIter>
std::vector<size_t> compute_freq(TIter b, TIter e, size_t radix, TIter tmp)
{
    std::vector<size_t> freq(256);
    for (auto it = b; it < e; ++it)
    {
        freq[it-b]++;
    }

    return freq;
}

std::vector<T> tmp(v.size());

// by high radix
template <class T>
void high_radix_sort(TIter b, TIter e, int radix)   
{
    if (radix < 0 || e - b < 2)
    {
        return;
    }

    auto freq = compute_freq(b, e, radix);
    auto begins = cumulative_sums(freq); 
    auto old_begins = begins;

    for (auto x : v)
    {
        auto index = begins[get_radix(x, radix)]++;
        (*tmp + index) = x;
    }

    for (int i = 0; i < count; ++i)
    {
        auto begin  = tmp + old_begins[i];
        auto end    = tmp + begins[i];

        std::vector<typename TIter::value_type> tmp2;
        high_radix_sort(begin, end, radix-1, tmp2);
        copy(begin, end, b + old_begins[i]);
    }
    
}

template <class TIter>
void radix_sort2(TIter b, TIter e)
{
    typedef typename TIter::value_type T;
    std::vector<T> buffer(e-b);
    const size_t radix_count = sizeof(T);

    high_radix_sort(b, e, radix_count, buffer.begin());
}
