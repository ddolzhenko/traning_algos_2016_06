#include <vector>

/*
struct S {
    uint32_t x : 4;
    uint32_t y : 4;
}
*/

template <class T>
uint8_t get_radix(T x, size_t radix)
{
    return x >> (radix * CHAR_BITS); 
    // return x / pow(256, radix);

    /*
    union Extractor {
        uint32_t number;
        uint8_t  digits[4];
    }
    */
}

template <class T>
std::vector<size_t> compute_freq(std::vector<T>& v, size_t radix)
{
    const size_t freq_size = izeof(T) << CHAR_BITS; // memory required O(1) because doesn't depend on n
    std::vector<size_t> freq(freq_size); //initialized with 0s

    for (auto x : v)
    {
        auto index = get_radix(x, radix);
        ++freq[x];
    }

    return freq; // C++ 11- MOVE-construtor will be called. No additional expenses. Otherwise - return by reference.
}

// implemented in STL
std::vector<size_t> cumulative_sums(const std::vector<size_t>& v)  //inplace ???
{
    std::vector<size_t> begins(v.size()); // initialized with 0s
    copy(v.begin(), v.end() - 1, begins.begin() + 1);

    for (size_t i = 1; i < v.size(); ++i)
    {
        //creating list of BEGINs for 0s, 1s, 2s, .... [0, 0, 2, 1, 1]
        begins[i] += begins[i-1];
        v[i+1]
    }

    return begins;
}

template <class T>
void radix_sort(std::vector<T>& v)   // O(c * n)
{
    const size_t radix_count = sizeof(T);  // ...

    std::vector<T> tmp(v.size());          // + O(n) additional memory

    for (size_t radix = 0; radix < radix_count; ++radix) // O(c)
    {
        //stable_sort_using_radix(v, radix);
        auto freq = compute_freq(v, radix);  // O(n)
        auto begins = cumulative_sums(freq); // O(1)

        for (auto x : v)                     // O(n)
        {
            auto index_begin = get_radix(x, radix);
            auto index = begins[index_begin];
            tmp[index] = x;
            begins[index_begin]++;
        }

        v.swap(tmp); // O(1) - because vector stores poiters ....
                     // or create 2 pointers and swap them
    }
}
