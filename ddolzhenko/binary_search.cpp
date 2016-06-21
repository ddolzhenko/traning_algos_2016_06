
int binary_search_recursive(int A[], int size, int key) {
    assert(size>=0);
    assert(std::is_sorted(A, A+size));
    
    if(size == 0)
        return -1;

    int m = size / 2;
    if(key < A[m])
        return binary_search(A, m, key);
    else if (A[m] < key)
        return m+1+binary_search(A+m+1, size-m-1, key);
    else
        return m;
}


int binary_search(int A[], int size, int key) {
    assert(size>=0);
    assert(std::is_sorted(A, A+size));
    
    while(size != 0)
    {
        // [0, m)[m][m+1, size)
        int m = size/2;
        if(key < A[m])
            size = m;   // [0, m)
        else if (A[m] < key)
        {
            A = A+m+1;  // [m+1, size)
            size -= m+1;
        }
        else
            return m;
    }

    return -1;
}

template <class TIter, class T>
TIter binary_search(TIter b, TIter e, const T& key) {
    assert(std::is_sorted(b, e));
    auto end = e;
    while(b < e) {
        TIter m = b + (e-b)/2;
        // [b, m) U [m] U [m+1, e)
        if(key < *m)
            e = m;      // [b, m)
        else if(*m < key)
            b = m+1;    // [m+1, e)
        else
            return m;
    }

    return end;
}


template <class TIter, class T>
TIter lower_bound(TIter b, TIter e, const T& key) {
    assert(is_sorted(b, e));
    while(b < e) {
        // [b, m) U [m] U [m+1, e)
        TIter m = b + (e-b)/2;
        if(*m < key)
            b = m+1; // m+1, e;
        else
            e = m; // [b, m)
    }

    return b;
}

template <class TIter, class T>
TIter upper_bound(TIter b, TIter e, const T& key) {
    assert(is_sorted(b, e));
    while(b < e) {
        // [b, m) U [m] U [m+1, e)
        TIter m = b + (e-b)/2;
        if(key < *m)
            e = m;
        else 
            b = m+1; // m+1, e;
    }

    return b;
}



template <class TIter, class T>
TIter binary_search(TIter b, TIter e, const T& key) {
    auto lb = lower_bound(b, e, key);

    if(lb != e && *lb == key)
        return lb;
    return e;
}


template <class TIter>
size_t count_7(TIter b, Titer e)
{
    return upper_bound(b, e) - lower_bound(b, e);
}