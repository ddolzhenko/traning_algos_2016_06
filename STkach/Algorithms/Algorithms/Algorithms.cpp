// Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Search_Lesson1.cpp"
#include <iostream>

using namespace std;


int main()
{
	int array[] = { 1, 3, 4, 2, 38, 3, 5 };
	int size = 7;

	cout << search_1(array, size, 38);

	char key;
	cin >> key;

    return 0;
}

