#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <vector>
#include "boundUpLowRemoveIf.hpp"

using namespace std;

template<class TExpect, class TFunc, class TParam2>
void test(TExpect expected, TFunc f, vector<int> param1, TParam2 param2)
{
   auto result = f(param1, param2);
   cout << "testing: " << expected << "==" << "f(";
   cout << "{";
   for (size_t i = 0; i < param1.size(); i++)
   {
      cout << param1[i] << ", ";
   } 
   cout << "} ";
   cout << ", " << param2 << ")" << endl;
   cout << string(20, '-')<< endl << (expected != result ? "FAIL" : "OK") << endl;
}

template <class TFunc>
void test_search_general(TFunc base_search_func)
{
   auto search_func = [=](vector<int> v, int key) {
      return base_search_func(&v[0], v.size(), key);
   };

   int key = 45;

   // key not in array
   typedef std::vector<int> Vec;
   // degenerated
   test(-1, search_func, Vec(), key);
   // trivial
   test(1, search_func, Vec({ 1 }), key);
   // trivial2nd
   test(-1, search_func, Vec({ 1, 1 }), key);
   test(-1, search_func, Vec({ 1, 2 }), key);
   test(-1, search_func, Vec({ 2, 1 }), key);

   // normal
   test(3, search_func, Vec({ 1, 1, 4, 45, 56 }), key);
   test(3, search_func, Vec({ 1, 1, 4, 45, 78, 100 }), key);

   //key in array
   // trivial
   test(0, search_func, Vec({ key }), key);

   // trivial2nd
   test(1, search_func, Vec({ 1, key }), key);
   test(0, search_func, Vec({ key, 92 }), key);
   test(0, search_func, Vec({ key, key }), key);

   // normal
   test(0, search_func, Vec({ 12, 45, 56, 74, 123, 156 }), key);
   test(5, search_func, Vec({ 1, 1, 1, 4, 23, key }), key);
   test(4, search_func, Vec({ 1, 1, 1, 4, key, 56, 75 }), key);
}

template <class T>
void testRemoveEven(std::vector<T> vec, std::vector<T> expected)
{
   bool res = true;
   size_t i = 0;
   cout << endl << "Testing:" << endl;
   cout << "remove_even from { ";
   for (size_t i = 0; i < vec.size(); i++)
   {
      cout << vec[i] << ", ";
   }
   cout << "}" << endl;
   cout << "Expected result: ";
   cout << "{ ";
   for (i = 0; i < expected.size(); i++)
   {
      cout << expected[i] << ", ";
   }
   cout << "}" << endl;
   
   int* end = remove_even(&vec[0], &vec[0] + vec.size());
   int* begin = &vec[0];
   i = 0;
   for (begin; begin < end; begin++)
   {
      if (*begin != expected[i]) res = false;
      i++;
   }
   cout << string(20, '-') << endl << "Test: " << (res ? "OK" : "FAIL") << endl;
}

template <class T, class TPredicat>
void testRemoveIf(std::vector<T> vec, std::vector<T> expected, TPredicat predicat)
{
   bool res = true;
   size_t i = 0;
   cout << endl << "Testing:" << endl;
   cout << "remove_if from { ";
   for (size_t i = 0; i < vec.size(); i++)
   {
      cout << vec[i] << ", ";
   }
   cout << "}" << endl;
   cout << "Expected result: ";
   cout << "{ ";
   for (i = 0; i < expected.size(); i++)
   {
      cout << expected[i] << ", ";
   }
   cout << "}" << endl;

   std::vector<int>::iterator end = remove_if(vec.begin(), vec.end(), predicat);
   std::vector<int>::iterator begin = vec.begin();
   i = 0;
   for (begin; begin < end; begin++)
   {
      if (*begin != expected[i]) res = false;
      i++;
   }
   cout << string(20, '-') << endl << "Test: " << (res ? "OK" : "FAIL") << endl;
}

/*
ostream& operator<<(ostream& o, const vector<int>& data)
{
   o << "{";
   for (const auto& x : data)
      o << x << ", ";
   return o << "}";
}
*/
#endif
