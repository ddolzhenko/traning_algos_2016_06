#include <vector>
#include <climits>

using namespace std;

template<class T>
void counting_sort(vector<T> v)
{
	const size_t freq_size = sizeof(T) << CHAR_BIT;
	vector<size_t> freq(freq_size);// O(1) struct size
	for (auto x : v)
	{
		freq[x]++;
	}

	size_t pos = 0;
	for (size_t x = 0; x < freq_size; ++x)
	{
		auto x_count = freq[x];
		for (size_t i = 0; i < x_count; ++i)
		{
			v[pos] = x;
			pos++;
		}
	}
}