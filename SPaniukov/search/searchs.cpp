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

/*
int search_3(int arr[], int size, int key)
{
   //assert(arr != 0);
   if (0 == size) return -1;
   int * temp = arr + size;
   *temp = key;
   //arr[size] = key;
   int i = 0;
   while (arr[i] != key) i++;
   if (size != i) return i;
   else return -1;
}
*/
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
