

template <class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T& key)
{
    while (b < e)
    {
        TIter m = b + (e - b)/2;

        // [b, m) U [m] U [m+1, e)

        if (*m < key) 
        {
            b = m + 1;     // all keys are to the right
        }
        else 
        {
            e = m;         // some keys are to the left
        }
    }

    return b;
}


template <class TIter, class T>
TIter lower_bound_rec(TIter b, TIter e, const T& key)
{
    if (b == e)
        return e;

    (*m < key) :
    ? return lower_bound_rec(m+1, e, key)
    : return lower_bound_rec(b, m, key);

}

template <class TIter, class T>
TIter binary_search_lb(TIter b, TIter e, const T& key)
{
    auto lb = lower_bound(b, e);

    if (lb != e && *Lb == key)  // HW: USE ONLY < !!!!!!
    {
        return lb;
    }

    return e;
}