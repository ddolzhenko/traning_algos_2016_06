#include "Search_Lesson1.cpp"


bool zeroSizeArray(int(*search_function)(int[]m, int size, int key));
bool oneElementArrayExist();
bool oneElementArrayNotExist();
bool twoElementsArrayExist();
bool twoElementsArrayNotExist();
bool searchElementFirst(); // 5 elements array
bool searchElementLast();  // 5 elements array
bool searchElementMid();   // 5 elemnets array
bool searchElementsNotExist() // 5 elements array

bool zeroSizeArray(int(*search_function)(int[]m, int size, int key))
{
	int array[] = {};
	size = 0;
	key = 0;
	bool result = false;

	int expected_value = -1;


}