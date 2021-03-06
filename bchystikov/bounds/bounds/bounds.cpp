#include "stdafx.h"
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

namespace my
{
   template<class TIter, class TKey>
   TIter lower_bound(TIter b, TIter e, const TKey & key)
   {
      assert(std::is_sorted(b , e));
      while (b < e)
      {
         TIter m = b + (e - b) / 2;
         if (*m < key)
         {
            b = m + 1;
         }
         else
         {
            e = m;
         }
      }
      return b;
   }

   template<class TIter, class TKey>
   TIter upper_bound(TIter b, TIter e, const TKey & key)
   {
      assert(std::is_sorted(b, e));
      while (b < e)
      {
         TIter m = b + (e - b) / 2;
         if (key < *m)
         {
            e = m;
         }
         else
         {
            b = m + 1;
         }
      }
      return b;
   }

   template<class TIter, class TKey>
   size_t find_keys_number(TIter b, TIter e, const TKey & key)
   {
      return (my::upper_bound(b, e, key) - my::lower_bound(b, e, key));
   }
}


int main()
{
   const int size = 10;
   int a[size] = { 1, 2, 2, 2, 6, 7, 7, 7, 8, 9 };
   std::vector<int> v = { 1, 2, 2, 2, 6, 7, 7, 7, 8, 9 };

   auto lb  = my::lower_bound(v.begin(), v.end(), 2);
   auto lbi = lb - v.begin();
   auto ub  = my::upper_bound(a, a + size, 2);
   auto ubi = ub - a;
   cout << "Lower_bound is " << *lb << ", index is " << lbi << endl;
   cout << "Upper_bound is " << *ub << ", index is " << ubi << endl;
   cout << "Number of " << 7 << " is " << my::find_keys_number(v.begin(), v.end(), 7) << endl;

   return 0;
}

