



template<class T>
radixSort(std::vector<T> v)
{

    std::vector<T> tmp;

    size_t radix_count = sizeof(T); // we process elements in 256 counting system. Each radix = byte.


    for (size_t radix = 0; radix < radix_count; ++radix)
    {
        std::vector<size_t> counts(radix_count);

        for (auto x : v)
        {
            // get radix
            auto radix = getRadix(x);
            
            // increase radix count at its position


        }

        // calculate cumulative summs
        // write elements from V to TMP according to cum_sums positions. Modify cum_sums after writing an element

        v.swap(tmp);
    }


    

}