int* search(int* b, int* e, int key)
{
    // we don't check Arr for EMPTY
    while (b < e)
    {
        if (*b == key)
        {
            break;
        }
        ++b;
    }

    // e culd be considered as NOT FOUND
    return b;
}