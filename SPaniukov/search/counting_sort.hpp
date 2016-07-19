#include <vector>
#include <climits>

using namespace std;

template<class T>
void counting_sort(vector<T> v)// o(n)
{
	const size_t freq_size = sizeof(T) << CHAR_BIT;
	vector<size_t> freq(freq_size);// O(1) struct size = size of type
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

template <class T>
uint8_t get_radix(T x, size_t radix)
{
	return x >> radix*CHAR_BIT;
}

template <class T>
vector<size_t> compute_frequencies(vector<T> v, size_t radix)
{
	const size_t freq_size = sizeof(T) << CHAR_BIT;
	vector<size_t> freq(freq_size);
	for (auto x : v)
	{
		auto index = get_radix(x, radix);
		freq[index]++;
	}
	return freq;
}

vector<size_t> cumulative_sums(vector<size_t>& v)
{
	vector<size_t> begins(v.size());
	copy(v.begin(), v.end() - 1, begins.begin() + 1);

	for (size_t i = 1; i < begins.size(); ++i)
	{
		begins[i] += begins[i - 1];
	}
	return begins;
}

template <class T>
void radix_sort(vector<T>& v)
{
	const size_t radix_size = sizeof(T);
	vector<T> buffer(v.size());

	for (size_t radix = 0; radix < radix_size; ++radix)
	{
		auto freq = compute_frequencies(v, radix);//O(n)
		auto begins = cumulative_sums(freq);//O(1)

		for (auto x : v)
		{
			auto index_begin = get_radix(x, radix);
			auto index = begins[index_begin];
			buffer[index] = x;
			begins[index_begin]++;
		}

		v.swap(buffer);
	}
}

