#include "searchs.hpp"

#include "sortedVector.hpp"
#include <vector>
#include <iostream>

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
	int arr[] = { 0, 3, 7, 6, 12, 7, 9, 4 };
	CSortedVector<int> sortVector = CSortedVector<int>(arr, arr + 8);
	CSortedVector<int> sortVector1 = sortVector;
	cout << "Sort vector :" << endl;
	cout << "{ ";
	for (size_t index = 0; index < sortVector1.size(); index++)
	{
		cout << sortVector[index] << ", ";
	}
	cout << "}" << endl;

   char ch;
   cin >> ch;
   
	return 0;
}

