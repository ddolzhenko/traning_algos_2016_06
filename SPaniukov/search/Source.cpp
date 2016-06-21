#include "searchs.hpp"
#include "boundUpLowRemoveIf.hpp"
#include "unit_tests.hpp"

void testSearch()
{
   cout << "******Test started*******" << endl;
   /*cout << "Testing search_1" << endl;
   test_search_general(search_1);
   cout << "Testing search_2" << endl;
   test_search_general(search_2);
   cout << "Testing search_4" << endl;
   test_search_general(search_4);*/
   test_search_general(binarySearchImperative);
   cout << "******Test finished*******" << endl;
}

int main()
{
	testSearch();

	return 0;
}

