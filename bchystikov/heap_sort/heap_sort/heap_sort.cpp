// heap_sort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "vector"
#include "algorithm"
#include "cassert"
using namespace std;
namespace HeapSort 
{
   size_t left(size_t i)
   {
      return 2 * i + 1;
   }

   size_t right(size_t i)
   {
      return 2 * i + 2;
   }

   size_t parent(size_t i)
   {
      assert(i > 0);
      return (i - 1) / 2;
   }

   bool is_root(size_t i)
   {
      return i == 0;
   }

   template<class T>
   void fix_heap_up(vector<T>& heap, size_t i)
   {
      if (is_root(i))
         return;

      size_t p = parent(i);
      if (heap[p] < heap[i])
      {
         swap(heap[p], heap[i]);
         fix_heap_up(heap, p);
      }
   }

   template<class T>
   void heap_push_back(vector<T>& heap, T x)//O(log n)
   {
      const size_t i = heap.size();
      heap.push_back(x);
      fix_heap_up(heap, i);
   }

   ///////////////////////////////////////////

   template<class T>
   size_t get_swap_index(vector<T>& heap, size_t l, size_t r)
   {
      const size_t size = heap.size();
      size_t result = size;

      if (r >= size) //r - invalid
      {
         result = l;
      }
      else if (l < size)//l && r - valid
      {
         result = (heap[r] > heap[l]) ? r : l;
      }

      return result;
   }

   template<class T>
   void heapify_down_my(vector<T>& heap, size_t i)
   {
      const size_t l = left(i);
      const size_t r = right(i);
      const size_t size = heap.size();

      const size_t swap_index = get_swap_index(vector<T>& heap, l, r);

      if (swap_index < size && heap[i] < heap[swap_index])
      {
         swap(heap[swap_index], heap[i]);
         heapify_down(heap, swap_index);
      }
   }

   template<class T>
   size_t get_swap_index(vector<T>& heap, size_t l, size_t r)
   {
      if (r >= heap.size())
      {
         return l;
      }
      return (heap[l] < heap[r]) ? r : l;
   }


   template<class T>
   void heapify_down_my(vector<T>& heap, size_t i)
   {
      //assert(is_heap(heap, left(i)));
      //assert(is_heap(heap, right(i)));
      const size_t l = left(i);
      const size_t r = right(i);
      const size_t size = heap.size();
      if (l >= size)     //i have no children
         return;

      size_t target = max_child(heap, l, r);

      if (heap[i] < heap[target])
      {
         swap(heap[target], heap[i]);
         heapify_down(heap, target);
      }

      //assert(is_heap(heap, i));

   }
}//namespace HeapSort

template<class TIter>
void heapify_up(TIter b, TIter e)
{
   if (e - b < 2)
      return;

   assert(is_heap(b, e - 1));

   auto last = e - 1;
   auto p = b + parent(last-b);
   if (*p < *last)
   {
      iter_swap(p, last);
      heapify_up(b, last);
   }

   assert(is_heap(b, e));
}

template<class TIter>
void build_max_heap(TIter b, TIter e)
{
   TIter bh = b;
   TIter eh = b;
   //[heap)[unprocessed)
   //[bh, eh)[eh,e)

   while (eh < e) //unprocessed exists
   {
      ++eh;
      heapify_up(bh, eh);
   }
}

template<class TIter>
void heap_sort(TIter b, TIter e)
{
   build_max_heap(b, e);

   //[heap)[sorted)
   //[b, eh)[eh,e)
   auto eh = e;
   while (b < eh)
   {
      eh--;
      iter_swap(b, eh);
      heapify_down(b, eh, b);
   }
}

int main()
{
    return 0;
}

