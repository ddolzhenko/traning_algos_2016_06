#include "searchs.hpp"
#include <cassert>

int search_1(int arr[], int size, int key)
{
   //assert(arr != 0);
   //assert(size >= 0);

   for (int i = 0; i < size; i++)
   {
      if (arr[i] == key) return i;
   }
   return -1;
}

int search_2(int arr[], int size, int key)
{
   //assert(arr != 0);
   int i = 0;
   while (i < size)
   {
      if (arr[i] == key) return i;
      i++;
   }
   return -1;
}

int search_4(int arr[], int size, int key)
{
  // assert(arr != 0);
   if (0 == size) return -1;

   int last = size - 1;
   int end = key;
   int save = arr[last];
   if (arr[last] == end) return last;
   else arr[last] = end;

   int i = 0;
   while (arr[i] != key) i++;
   arr[last] = save;
   if (last != i) return i;
   else return -1;
}


int binarySearchRecursive(int arr[], int size, int key)
{
	if (0 == size) return -1;

	int middle = size / 2;
	if ( key < arr[middle] )
	{
		return binarySearchRecursive(arr, middle, key);
	}
	else if (arr[middle] < key)
	{
		return middle + 1 + binarySearchRecursive(arr + middle+1, size-middle-1, key);
	}
	else
	{
		return middle;
	}
}

int binarySearchImperative(int arr[], int size, int key)
{
	while (0 != size)
	{
		//[0, middle)[middle](middle+1, size]
		int middle = size / 2;
		if (key < arr[middle]) //[0, middle)
		{
			size = middle;
		}
		else if (arr[middle] < key)//(middle+1, size]
		{
			arr = arr + middle + 1;
			size -= middle + 1;
		}
		else
		{
			return middle;
		}
	}
	return 0;
}


int searchMinElement(int arr[], int size)
{
	int temp = arr[0];
	for (int i = 0; i < size; i++)
	{

		if (arr[i] < temp) temp = arr[i];
	}
	return temp;
}



int* searchPointerMinElement(int* b, int* e)
{
	int* temp = NULL;
	while (b < e)
	{
		if (*b < *temp) temp = b;
      b++;
	}
	return temp;
}