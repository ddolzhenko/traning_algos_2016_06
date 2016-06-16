
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
