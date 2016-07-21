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
   if (e - b > 1)
   {
      TIter m = b + (e - b) / 2;
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
   assert(e - b > 0);
   //[b, bu) U [bu, eu) U [eu, e)
   //[<) U [unsorted) U [>=)
   auto pivot = e - 1;
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
         iter_swap(bu, eu - 1);
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

   iter_swap(pivot, e - 1);
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
   quick_sort(pivot + 1, e);

   assert(is_sorted(b, e));
}

template <class T>
void counting_sort(vector<T>& v) //radix O(1)
{  //will not work for 4 byte T
   const size_t freq_size = sizeof(T) << CHAR_BIT;
   vector<size_t> freq(freq_size);
   for (auto x : v)
   {
      freq[x]++;
   }

   size_t pos = 0;
   for (size_t x = 0; x < freq_size; ++x)
   {
      auto x_count = freq[x];
      for (size_t i = 0; i < x_count; ++i)
      {
         v[pos] = x;
         ++pos;
      }
   }
}

//union extractor {
//   uint32_t number;
//   uint32_t digits[4];
//};

//struct S
//{
//   uint32_t x : 4;
//   uint32_t y : 4;
//};

template <class T>
uint8_t get_radix(T x, size_t radix)
{
   return x >> (radix * CHAR_BIT);
   //return x / (pow(256, radix));
}

template <class T>
vector<size_t> compute_frequencies(vector<T>& v, size_t radix) //O(n)
{
   const size_t freq_size = sizeof(T) << CHAR_BIT;
   vector<size_t> freq(freq_size);
   for (auto x : v)
   {
      auto index = get_radix(x, radix);
      freq[x]++;
   }
   return freq;
}

vector<size_t> cumulative_sum(vector<size_t>& v)   //O(1)
{
   vector<size_t> begins(v.size(), 0);
   copy(v.begin(), v.end() - 1, begins.begin() + 1);

   for (size_t i = 1; i < begins.size(); ++i)
   {
      begins[i] += begins[i - 1];
   }
   return begins;
}

template <class T>
void radix_sort(vector<T>& v)
{
   const size_t radix_count = sizeof(T);

   vector<T> buffer(v.size());

   for (size_t radix = 0; radix < radix_count; ++radix)
   {
      auto freq = compute_frequencies(v, radix);
      auto begins = cumulative_sum(freq);
      for (auto x : v)
      {
         auto index_begin = get_radix(x, radix);
         auto index = begins[index_begin];
         buffer[index] = x;            //jumps
         ++begins[index_begin];
      }
      v.swap(buffer);
   }
}

template <class Titer>
vector<size_t> compute_frequencies(Titer b, Titer e)
{
   vector<size_t> freq(256);
   for (auto it = b; it != e; ++it)
      freq[it - b]++;
   return freq;
}

template <class TIter>
void radix_sort_upsidedown(TIter b, TIter e, int radix, TIter buff)
{
   if (e - b < 2 || radix < 0)
      return;

   auto freq = compute_frequencies(b, e);
   auto begins = cumulative_sum(freq);
   auto begins_old = begins;

   for (auto x : begins_old)
   {
      auto index = begins[get_radix(x, radix)]++;  // begin >> end
      *(buff + index) = x;
   }
   for (size_t i = 0; i < begins_old.size(); ++i)
   {
      auto begin = buff + begins_old[i];
      auto end   = buff + begins[i];
      vector<typename TIter::value_type> buff2;
      radix_sort_upsidedown(begin, end, radix-1, buff2.begin());
      copy(begin, end, b+begins_old[i]);
   }
}

template <class TIter>
void radix_sort2(TIter b, TIter e)
{
   typedef typename TIter::value_type T;
   const size_t radix_count = sizeof(T);
   vector<T> buffer(e-b);
   radix_sort_upsidedown(b, e, radix_count, buffer.begin());
}



int main()
{
   int arr[] = { 12, 11, 13, 5, 6, 7 };
   vector<unsigned int> v = { 412, 511, 213, 115, 996, 137 };
   //int arr[] = { 8, 1, 15, 3, 2 };
   const int arr_size = sizeof(arr) / sizeof(arr[0]);
   //int buffer[arr_size];
   //merge_sort(arr, arr + arr_size, buffer);
   quick_sort(arr, arr + arr_size);
   //radix_sort(v);
   radix_sort2(v.begin(), v.end());
   for (int i = 0; i < arr_size; ++i)
      cout << v[i] << ' ';
   system("pause");
   return 0;
}

