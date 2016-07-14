#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

template <class TIter>
void merge(TIter b, TIter m, TIter e, TIter out_begin)   //O(n)
{
   TIter i = b;
   TIter j = m;
   TIter out_end = out_begin;
   while (i < m && j < e)
   {
      assert(is_sorted(out_begin, out_end));
      if (*i < *j)
      {
         *out_end = *i;
         ++i;
      }
      else
      {
         *out_end = *j;
         ++j;
      }
      ++out_end;
      assert(is_sorted(out_begin, out_end));
   }

   out_end = copy(i, m, out_end);
   out_end = copy(j, e, out_end);

   assert(is_sorted(out_begin, out_end));
   assert((out_end - out_begin) == (e - b));
}

template <class TIter>
void merge_sort(TIter b, TIter e, TIter buff)   //O(n*log n) - always + O(n) дополнительной памяти
{
   //[b, e) = [b, m) U [m, e)
   //assert(e >= b);
   if (e-b > 1)
   {
      TIter m = b + (e-b)/2;
      merge_sort(b, m, buff);
      merge_sort(m, e, buff);
      merge(b, m, e, buff);
      copy(buff, buff + (e - b), b);
   }
}

template <class T>
void swap(T& x, T& y)
{
   T tmp = x;
   x = y;
   y = tmp;
}

template <class T>
void swap(std::vector<T>& x, std::vector<T>& y)
{
   x.swap(y);
}

template <class T>
void merge_sort_helper(std::vector<T> & v, std::vector<T> & buff)
{
   if (v.size() < 2)
      return;

   auto m = v.size() / 2;
   merge_sort(b, m);
   merge_sort(m, e);

}

template <class T>
void merge_sort2(std::vector<T> & v)
{
   std::vector<T> buff(v.size());
   merge_sort_helper(v, buff);
}

template <class TIter>
TIter partition_my(TIter b, TIter e, TIter p)
{
   TIter result = p;

   for (TIter i = b; i < p; ++i)
   {
      if (*i > *result)
      {
         std::swap(*i, *result);
      }
   }

   for (TIter i = p; i < e; ++i)
   {
      if (*i < *result)
      {
         std::swap(*i, *result);
      }
   }
   return result;
}

template <class TIter>
TIter partition_hoar(TIter b, TIter e)
{
   assert(e-b > 0);
   //[b, bu) U [bu, eu) U [eu, e)
   //[<) U [unsorted) U [>=)
   auto pivot = e-1;
   TIter bu = b;
   TIter eu = pivot;

   while (bu < eu)
   {
      //assert(*max_element(b, bu) <  *pivot);
      //assert(*min_element(eu, beu) >=  *pivot);
      if (*bu < *pivot)
      {
         //[<) U [u1] U [unsorted) U [>=)
         ++bu;
      }
      else
      {
         iter_swap(bu, eu-1);
         --eu;
      }
      //assert(*max_element(b, bu) <  *pivot);
      //assert(*min_element(eu, beu) >=  *pivot);
   }
   iter_swap(pivot, eu);
   return eu;
}

template <class TIter>
TIter partition(TIter b, TIter e, TIter pivot)
{
   //[<)[>-)[unpartitioned)
   //[b, el][el, bu)[bu,e)
   //[b, bg][bg, eg)[eg, e)

   iter_swap(pivot, e-1);
   pivot = e;
   --pivot;

   auto p_value = *pivot;
   auto bg = b;
   auto eg = b;

   while (eg < pivot)
   {
      //assert(*max_element(b, bg) <  *pivot);
      //assert(*min_element(bg, eg) >=  *pivot);

      if (*eg < p_value)
      {
         iter_swap(bg, eg);
         bg++;
      }
      eg++;
   }
   iter_swap(pivot, eg);
   return eg;
}

template <class TIter>
void quick_sort(TIter b, TIter e)
{
   if (e - b < 2)
      return;

   TIter pivot = b;
   // [b, p) [p, e)
   pivot = partition_hoar(b, e);
   //assert(*max_element(b, pivot) <  *pivot);
   //assert(*min_element(pivot, e) >= *pivot);
   
   quick_sort(b, pivot);
   quick_sort(pivot+1, e);

   assert(is_sorted(b, e));
}

int main()
{
   int arr[] = { 12, 11, 13, 5, 6, 7 };
   //int arr[] = { 8, 1, 15, 3, 2 };
   const int arr_size = sizeof(arr) / sizeof(arr[0]);
   //int buffer[arr_size];
   //merge_sort(arr, arr + arr_size, buffer);
   quick_sort(arr, arr + arr_size);
   for (int i = 0; i < arr_size; ++i)
      cout << arr[i] << ' ';
    system("pause");
   return 0;
}

