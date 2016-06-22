// Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lower_bound.h"
#include <iostream>

using namespace std;


int main()
{
	//test_search();

	int a[] = {2, 2, 3, 3, 3, 4, 5};

	int *n = remove_even(a, a + 7);

	cout << *n << "\n";

	for (int i = 0; i < 7; ++i)
	{
		cout << a[i];
	}
	
	

	char key;
	cin >> key;

    return 0;
}

