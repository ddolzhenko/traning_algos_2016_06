int *min_search(int *b, int *e, int key)
{
    int *min = b;

    while (++b < e)
    {
        if (*b < *min)
        {
            min = b
        }
    }

    return min;
}

// 1 or log N
int *bin_search1(int *b, int *e, int key)
{
    while (b < e)
    {
        // there are two comprassions!!

        int *m = b + (e - b) / 2;
        if (*m < key)
            e = m; // [b, m)
        else if (*m > key)
            b = m + 1; // [m ,e)
        else
            return m; // [m]
    }
    return e;
}

// first element of the sequence
// always log N
int *lower_bound(int *b, int *e, int key)
{
    while (b < e)
    {
        int *m = b + (e - b) / 2;

        if (*m < key) // only one comprassion
            b = m + 1;
        else
            e = m;
    }
    return e;
}

// always 1 + log N
int *bin_search2(int *b, int *e, int key)
{
    int *lb = lower_bound(b, e, key);

    if (lb != e && *lb == key) // DZ: write wihout comprasion operator!!!
        return lb;
    return e;
}

int main()
{
    return 0;
}
