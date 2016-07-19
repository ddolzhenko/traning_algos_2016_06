#include "Header.h"

template <class T>
int numDigits(T number)
{
	int digits = 0;
	if (number < 0) digits = 1; // remove this line if '-' counts as a digit
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

void my_radix_sort(vector<size_t> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		size_t number = v[i];
		size_t lastDigit = number % 10;
		for (int j = 0; j < numDigits(v[i]); ++j)
		{
			
		}
	}
}