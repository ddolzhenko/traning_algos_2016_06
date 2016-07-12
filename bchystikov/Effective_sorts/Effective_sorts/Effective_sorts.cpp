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
void merge_sort(TIter b, TIter e, TIter buff)
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

int main()
{
   //int arr[] = { 12, 11, 13, 5, 6, 7 };
   //const int arr_size = sizeof(arr) / sizeof(arr[0]);
   //int buffer[arr_size];
   //merge_sort(arr, arr + arr_size, buffer);
   //for (int i = 0; i < arr_size; ++i)
   //   cout << arr[i] << endl;
   // system("pause");
   return 0;
}

template <class T>
class vector
{
public:
   vector(size_t size = 0)
   : m_size(0)
   , m_data(nullptr)
   , m_capacity(0)
   {
      m_data = new T[size];
      m_size = size;
      m_capacity = size;
   }

   vector(const vector<T>& that)
      : m_size(0)
      , m_data(nullptr)
      , m_capacity(0)
   {
      m_data = new T[other.size()];
      m_size = other.size();
      m_capacity = other.capacity();
      std::copy(other.begin(), other.end(), m_data);
   }

   ~vector()
   {
      delete [] m_data;
   }

   void swap(vector<T>& other) noexept
   {
      std::swap(m_data, other.data);
      std::swap(m_size, other.m_size);
      std::swap(m_capacity, other.m_capacity);
   }

   void reserve(size_t new_size)
   {
      if (m_capacity < new_size)
      {
         T* tmp = new T[new_size];
         copy(begin(), end(), tmp);
         delete[] m_data;
         m_data = tmp;
         m_capacity = new_size
      }
   }

   //---------------------------

   vector<T>& operator=(const vector<T>& that)  
   {
      if(this != &other)
         this->swap(vector<T>(other));   //copy swap idiom!
   }

   T& operato[](size_t index)
   {
      return m_data[index];
   }

   const T& operato[](size_t index) const
   {
      return m_data[index];
   }
  //vector<T>& operator=(vector<T> that)  
   //{
   //     this->swap(other);   //copy swap idiom!
   //}

   T* begin()
   {
      return m_data;
   }

   T* end()
   {
      return m_data+m_size;
   }

   void push_back(const T& x)
   {
      assert(m_capacity >= m_size);
      if (m_capacity ==  m_size)
      {
         reserve(m_size*2);
      }
      *(end()) = x;
      ++m_size;
      assert(m_capacity >= m_size);
   }

   size_t size() const
   {
      return m_size;
   }

private:
   T*       m_data;
   size_t   m_size;
   size_t   m_capacity;
};
