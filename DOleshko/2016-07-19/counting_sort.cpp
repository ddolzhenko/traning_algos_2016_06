#include <vector>


void counting_sort(std::vector<uint8_t>& v)
{
    const size_t freq_size = 1 << CHAR_BITS; // memory required O(1) because doesn't depend on n

    std::vector<size_t> freq(freq_size); //initialized with 0s

    for (auto x : v)
    {
        ++freq[x];
    }

size_t pos = 0;
    for (size_t x = 0; x < freq_size; ++i)
    {
        for (size_t i = 0; i < freq[x]; ++i)
        {
            v[pos] = x;
            ++pos;
        }
    }
}

template <class T>
void counting_sort_T(std::vector<T>& v)
//will work for 1byte 2byte elements
{
    const size_t freq_size = sizeof(T) << CHAR_BITS; // memory required O(1) because doesn't depend on n

    std::vector<size_t> freq(freq_size); //initialized with 0s

    for (auto x : v)
    {
        ++freq[x];
    }

size_t pos = 0;
    for (size_t x = 0; x < freq_size; ++i)
    {
        for (size_t i = 0; i < freq[x]; ++i)
        {
            v[pos] = x;
            ++pos;
        }
    }
}
