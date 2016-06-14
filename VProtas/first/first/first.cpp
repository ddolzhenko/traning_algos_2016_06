#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

const int INVALID_INDEX = -1;

ostream& operator<< (ostream& o, const std::vector<int>& data)
{
   o << "{";
   for (const auto& x : data)
   {
      o << x << ", ";
   }      
   return o << "}";
}

const int linearSearch_2(const int arr[], const int arrSize, const int key)
{
   //assert(arr != 0);
   assert(arrSize >= 0);
   for (int i = 0; i < arrSize; i++)
   {
      if (arr[i] == key)
      {
         return i;
      }
   }
   return INVALID_INDEX;
}

template<class TExpect, class TFunc, class TParam1, class TParam2>
void test(TExpect expected, TFunc func, TParam1 param1, TParam2 param2)
{
   auto result = func(param1, param2);
   cout << "testing: " << expected << " == " << "f(" << param1 << ", " << param2 << ") = " << result << endl;
   cout << string(80, "-") << ((expected != result) ? "fail" : "ok") << endl;
}

template<class TFunc>
void test_search_general(TFunc base_search_func)
{
   auto search_func = [=](std::vector<int> v, int key)
   {
      if(v.size() == 0)
         return base_search_func(0, v.size(), key);
      return base_search_func(&v[0], v.size(), key);
   };
   const int key = 42;
   //key not in array test
   typedef std::vector<int> Vec;
   //degenerated
   test(-1, search_func, Vec(), key);

   //trivial
   test(-1, search_func, Vec({ 1 }), key);

   //trivial2
   test(-1, search_func, Vec({ 1, 1 }), key);
   test(-1, search_func, Vec({ 1, 2 }), key);
   test(-1, search_func, Vec({ 2, 1 }), key);

   //normal
   test(-1, search_func, Vec({ 1, 1, 4, 56, 23 }), key);
   test(-1, search_func, Vec({ 1,1,4,56,23, -100 }), key);

   //key in array

   //trivial
   test(-1, search_func, Vec({ key }), key);

   //trivial2
   test(-1, search_func, Vec({ 1, key }), key);
   test(-1, search_func, Vec({ key, 2 }), key);
   test(-1, search_func, Vec({ key, key }), key);

   test(-1, search_func, Vec({ key, 1, 4, 56, 23 }), key);
   test(-1, search_func, Vec({ 1, 5, key, 56, 23 }), key);
   test(-1, search_func, Vec({ 1, 1, 4, 56, 23, -key }), key);
}

void test_search()
{
   test_search_general(linearSearch_2);
}

const int linearSearch(const int arr[], const int arrSize, const int key);

const int searchWithAdd(const int arr[], const int arrSize, const int key);

const int searchWithNoAdd(int arr[], const int arrSize, const int key);

int main()
{
   /*const int size = 6;
   int arr[size] = { 2, 4, 6, 8, 10, 12 };
   cout << linearSearch(arr, size, 12) << endl;
   cout << searchWithAdd(arr, size, 12) << endl;
   cout << searchWithNoAdd(arr, size, 12) << endl;
   system("pause");*/
   test_search();
   return 0;
}

const int linearSearch(const int arr[], const int arrSize, const int key)
{
   if (arrSize <= 0)
   {
      return INVALID_INDEX;
   }
   for (int i = 0; i < arrSize; i++)
   {
      if (arr[i] == key)
      {
         return i;
      }
   }
   return INVALID_INDEX;
}


const int searchWithAdd(const int arr[], const int arrSize, const int key)
{
   if (arrSize <= 0)
   {
      return INVALID_INDEX;
   }
   const int newSize = arrSize + 1;
   int * p = new int[newSize];
   for (int i = 0; i < arrSize; i++)
   {
      p[i] = arr[i];
   }
   p[newSize - 1] = key;
   int index = INVALID_INDEX;
   for (int i = 0; i < newSize; i++)
   {
      if (p[i] == key)
      {
         index = i;
         break;
      }
   }
   if (p)
   {
      delete p;
   }
   return index != newSize - 1 ? index : INVALID_INDEX;
}

const int searchWithNoAdd(int arr[], const int arrSize, const int key)
{
   if (arrSize <= 0)
   {
      return INVALID_INDEX;
   }
   if (arr[arrSize - 1] != key)
   {
      const int last = arr[arrSize - 1];
      arr[arrSize - 1] = key;
      int foundElement = INVALID_INDEX;
      for (int i = 0; i < arrSize; i++)
      {
         if (arr[i] == key)
         {
            foundElement = i;
            break;
         }
      }
      arr[arrSize - 1] = last;
      return foundElement != arrSize - 1 ? foundElement : INVALID_INDEX;
   }
   else
   {
      return arrSize - 1;
   }
}