// Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Search_Lesson1_Test.cpp"
#include "Min_search.h"
#include <iostream>

using namespace std;


int main()
{
	//test_search();

	int a[] = {8, 2, 3, 4};

	cout << *min_search(a, a + 4);
	
	char key;
	cin >> key;

    return 0;
}

