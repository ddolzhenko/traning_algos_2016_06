#include "searchs.hpp"
#include "unit_tests.hpp"
//#include <iostream>

//using namespace std;

void testSearch()
{
   cout << "******Test started*******" << endl;
   cout << "Testing search_1" << endl;
   test_search_general(search_1);
   cout << "Testing search_2" << endl;
   test_search_general(search_2);
//   cout << "Testing search_3" << endl;
//   test_search_general(search_3);
   cout << "Testing search_4" << endl;
   test_search_general(search_4);

   cout << "******Test finished*******" << endl;
}

int main()
{
	testSearch();
	return 0;
}

