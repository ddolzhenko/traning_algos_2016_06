template <class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T& key)
{
    while (b < e)
    {
        // [b, m) U [m] U [m+1, e)
/*
        if (*m <= key)
            b = m + 1;    // [m+1, e)

        if (key < *m)
            e = m;

        if (key == *m)
            b = m + 1
*/
        
        if (key < *m)
            e = m;
        else
            b = m + 1;

    }

    return b;
}