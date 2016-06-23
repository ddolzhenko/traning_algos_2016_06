#ifndef SEARCHS_HPP
#define SEARCHS_HPP
#include <cassert>

int search_1(int arr[], int size, int key);
int search_2(int arr[], int size, int key);
int search_4(int arr[], int size, int key);

int binarySearchRecursive(int arr[], int size, int key);
int binarySearchImperative(int arr[], int size, int key);

int searchMinElement(int arr[], int size);
int* searchPointerMinElement(int* b, int* e);


template<class TIter, class T>
TIter bynarySearch(TIter begin, TIter end, const T& key)
{
	assert(std::is_sorted(begin, end));

	TIter temp = end;
	while (begin < end)
	{
		TIter middle = begin + (end - begin) / 2;
		// [begin, middle) and [middle] and (middle, end]
		if (key < *middle) end = middle; //[begin, middle)
		else if (key > *middle) begin = middle+1;// (middle, end]
		else return middle; //[middle]
	}
	return temp;
}
/*
template<class TIter, class T>
TIter lowerBound(TIter begin, TIter end, const T& key)
{
	assert(std::is_sorted(begin, end));

	while (begin < end)
	{
		TIter middle = begin + (end - begin) / 2;
		// [begin, middle) and [middle] and [middle+1, end)
		if (*middle < key) begin = middle + 1; //[middle+1, end)
		else end = middle;
	}
	return end;
}
*/
template<class TIter, class T>
TIter bynarySearch1(TIter begin, TIter end, const T& key)
{
	TIter lb = lowerBound(begin, end, key);

	if (*lb != end && *lb == key) return lb;
	else end;
}

#endif

