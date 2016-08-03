#include <vector>
#include <iostream>

#include "sortedVector.hpp"
#include "CList.hpp"

using namespace std;
/*
void testSearch()
{
   cout << "******Test started*******" << endl;
   cout << "******Test finished*******" << endl;
}

void testRemoveEvenGeneral()
{
   typedef std::vector<int> Vec;
   cout << "******Test started*******" << endl;
   //testRemoveEven(Vec(), Vec());
   testRemoveEven(Vec({ 2 }), Vec());
   testRemoveEven(Vec({ 1 }), Vec({ 1 }));
   testRemoveEven(Vec({ 1, 2 }), Vec({ 1 }));
   testRemoveEven(Vec({ 2, 2 }), Vec());
   testRemoveEven(Vec({ 0, 3, 7, 6, 12, 7, 9, 4 }), Vec({ 3, 7, 7, 9 }));
   testRemoveEven(Vec({ 0, 2, 4, 6, 12, 2, 2, 1 }), Vec({ 1 }));
  // testRemoveIf(Vec(), Vec(), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 2 }), Vec(), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 0, 2 }), Vec(), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 1 }), Vec({ 1 }), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 1, 2 }), Vec({ 1 }), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 2, 2 }), Vec(), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 0, 3, 7, 6, 12, 7, 9, 4 }), Vec({ 3, 7, 7, 9 }), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 0, 3, 7, 6, 12, 7, 9, 4 }), Vec({ 3, 7, 7, 9 }), isEven<std::vector<int>::iterator>);
   testRemoveIf(Vec({ 0, 2, 4, 6, 12, 2, 2, 1 }), Vec({ 1 }), isEven<std::vector<int>::iterator>);
   cout << "******Test finished*******" << endl;
}
*/

int main()
{
	DLL::CList<int> list1 = DLL::CList<int>();
	DLL::ListIterator<int> begin = list1.begin();
	DLL::ListIterator<int> end = list1.end();

	if (begin == end) cout << "welcome to the club" << endl;


	char ch;
   cin >> ch;
   
	return 0;
}

