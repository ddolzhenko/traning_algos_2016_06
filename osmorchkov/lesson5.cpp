void merge(int *b, int* m, int *e, int []output)
{
    int *output_end = output;

    int *i = b;
    int *j = e;

    while (i < m && j < e)
    {
        assert ( std::is_sorted(i, m) );
        assert ( std::is_sorted(j, e) );

        assert( std::is_sorted(output, cursor) );

        if (*i < *j)
        {
            *output_end = *i++;
        }
        else
        {
            *output_end = *j++;
        }
        ++output_end;

        assert ( std::is_sorted(i, m) );
        assert ( std::is_sorted(j, e) );

        assert( std::is_sorted(output, cursor) );
    }

    output_end = std::copy(i, m, output_end);
    output_end = std::copy(j, e, output_end);

    assert( std::is_sorted(output, cursor) );
    assert( output_end - output == e - b );
}

void merge_sort(int *b, int *e, int []buffer)
{
    if (e - b > 1) //size at least == 2
    {
        // [b, e) = [b, m) U [m, e)
        int *m = b + (e - b) / 2;

        merge_sort(b, m, buffer);
        merge_sort(m, e), buffer;

        merge(b, m, e, buffer);

        std::sopy(buffer, buffer + (e - b), b);
    }

    assert(std::is_sorted(b, e));
}