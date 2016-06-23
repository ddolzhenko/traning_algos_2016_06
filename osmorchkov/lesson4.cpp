int *min_search(int *b, int *e)
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

// O(logN)
// [1, 2, 3, 4, 5, 6, 7, 8, 9] where search element is 4:
// [1, 2, 3, 4]
// [4]
int *lower_bound(int *b, int *e, int key) //+1(=), +1(=), +1(=)
{
    while (b < e) //+1(==)
    {
        int *m = b + (e - b) / 2; //+1(=), +1(+), +1(-), +1(/)

        if (*m < key) //+1(==)
            b = m + 1; // +1(=), +1(+)
        else
            e = m; //+1(=)
    }
    return e; //+1(=)

    // So, T(n, fi) => 7(=) + 2(==) + 1(+) + 1(-) + 1(/) + fi(1(+)) => T(12, 1)
}

int *upper_bound(int *b, int *e, int key)
{
    while (b < e)
    {
        int *m = b + (e - b) / 2;

        if (key < *m)
            e = m;
        else
            b = m + 1;
    }
    return e;
}

int count(int *b, int *e, int key)
{
    return upper_bound(b, e, key) - lower_bound(b, e, key); // O(logN)
}

// O(1/2 * n^2) - O(1/2 * n) = O(n^2)
void my_sort(int *b, int *e)
{
    for (int *i = b; b < e; ++i)
    {
        assert(std::is_sorted(b, i));

        for (int *j = i + 1; j < e; ++j)
        {
            assert(*i == std::min(*i, *j));

            if (*i > *j)
            {
                int tmp = *i;
                *i = *j;
                *j = tmp;
            }

            assert(*i == std::min(*i, *j));
        }

        assert(std::is_sorted(b, i));
    }

    assert(std::is_sorted(b, e));
}

// O(n^2)
void selection_sort(int *b, int *e)
{
    for (int *i = b; b < e; ++i)
    {
        // [sorted) [unsorted)
        // [b, i),  [i, e)
        assert(std::is_sorted(b, i));

        int *min_el = min_search(i, e);
        int tmp = *i;
        *i = *min_el;
        *min_el = tmp;

        assert(std::is_sorted(b, i));
    }

    assert(std::is_sorted(b, e));
}

void my_bubble(int *b, int *e)
{
    for (int *i = e; i != b; --i)
    {
        // [unsorted) [sorted)
        // [b, i),    [i, e)
        assert(is_sorted(i, e));

        for (int j = b + 1; j < i; ++j)
        {
            // [b, j-1) [j-1] [j] [j+1, i)

            //assert(j == max_element(b, j));

            int *prev = j - 1;
            if (*j < *prev)
            {
                int tmp = *prev;
                *prev = *j;
                *j = prev;
            }

            //assert(j == max_element(b, j));
        }

        assert(is_sorted(i, e));
    }
}

void insertion_sort(int *b, int *e)
{
    // [sorted) [unsorted)
    // [b, i)   [i, e)
    for (int *i = b; i < e; ++i)
    {
        assert(std::is_sorted(b, i));

        for (int *j = i; j > b; --j)
        {
            // [b, j) [j] [j + 1, i + 1)
            assert(std::is_sorted(b, j));
            assert(std::is_sorted(j, i));

            int *prev = j - 1;
            if (*j < *prev)
            {
                int tmp = *prev;
                *prev = *j;
                *j = prev;
            }
            else break;

            assert(std::is_sorted(b, j));
            assert(std::is_sorted(j, i));
        }

        assert(std::is_sorted(b, i));
    }
}

int main()
{
    return 0;
}
