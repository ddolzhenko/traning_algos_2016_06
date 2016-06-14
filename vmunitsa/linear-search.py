def search_linear(arr, size, search):
    for index,el in enumerate(arr):
        if el == search:
            return index
    return -1

def binary_search(arr, size, search):
    if size == 0: return -1
    if size == 1:
        if arr[size - 1] == search:
            return 0
        else:
            return -1
        
    middle_index = int(0.5*size)+1
    print 'middle index: ', middle_index
    while (middle_index != 1):
        if arr[middle_index]  == search:
            return middle_index

        if  search > arr[middle_index]:
            middle_index = int(0.5*middle_index) + 1

        if search < arr[middle_index]:
            middle_index = int(0.5*middle_index)


# binary search tests
test_arrays = [
    [],
    [1],                        # trivial neg
    [1202],                     # trivial positive
    [1,2,45,35,68,79,88,1202,1556,9999], # usual positive
    [12,43,50,79,880,1202,1202,1556,9999], # usual double results
    [1,2,45,35,68,79,88,156,999],          # usual negative
]

for array in test_arrays:
    search = 1202
    print 'binary search is searches for', search, ' in ', array
    print 'result: ', binary_search(array, len(array), 1202)

    print 'linear search searches for', search, ' in ', array
    print 'result: ', search_linear(array, len(array), 1202)


