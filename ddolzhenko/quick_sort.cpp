


template <class TIter>
TIter partition_hoar(TIter b,TIter e) {
    assert(e-b > 0);

    auto pivot = e-1;

    // [b, bu) U [bu, eu) U [eu, e)
    // [ <   ) U [unsort) U [ >=  )
    auto bu = b;
    auto eu = pivot;
    while(bu < eu) {
        //assert(*max_element(b, bu) < pivot_value);
        //assert(*min_element(eu, e) >= pivot_value);

        if(*bu < *pivot) {
            // [ <   ) [u1] (unsort) U [ >=  )
            bu++;
        } else {
            // [ <   ) [bu] [bu+1, eu-1) [eu-1] U [ >=  )
            iter_swap(bu, eu-1);
            eu--;
        }
        //assert(*max_element(b, bu) < pivot_value);
        //assert(*min_element(eu, e) >= pivot_value);
    }

    iter_swap(pivot, eu);
    return eu;
}


TIter partition_2(TIter b, TIter e, TIter pivot) {
    assert(e-b > 1);

    // [< )     [ >= )      [unpartitioned)
    // [b, bg)  [bg, eg)    [eg, e)
    iter_swap(pivot, e-1);
    pivot = e;
    pivot--;

    auto bg = b;
    auto eg = b;
    while(eg < pivot) {
        // assert(*max_element(b, bg) < pivot_value)
        // assert(*min_element(bg, eg) >= pivot_value)
        if(*eg < *pivot) {
            iter_swap(bg, eg);
            bg++;
        }
        eg++;            
    }

    iter_swap(pivot, eg);
    return eg;
}

void quick_sort(b, e, depth=0) {

    // if (depth > 10*log(2, n))
    // {
    //     insertion_sort(e-b);
    //     return;
    // }

    if(e-b < 2)
        return;

    auto pivot = b + (e-b)/2;

    // [b, p) [p, e)
    pivot = partition(b, e, pivot);

    assert(*max_element(b, pivot) < *pivot);
    assert(*min_element(pivot, e) >= *pivot);

    quick_sort(b, pivot, depth+1);
    quick_sort(pivot+1, e, depth+1);

    assert(is_sorted(b, e));
}