
template<class T>
uint8_t get_radix(T x, size_t radix)
{
	return x >> radix*CHAR_BIT;
}


template<class T>
vector<size_t> compute_freq(vector<T>& vec, size_t radix)
{
	const size_t freq_size = sizeof(T) << CHAR_BIT;
	vector<size_t> freq(freq_size);
	for(auto X : vec)
	{
		auto index = get_radix(X, radix);
		freq[index]++;
	}
	return freq;
}

template <class T>
vector<size_t> cumulative_sums(vector<T>& vec)
{
	vector<size_t> freq_begins(vec.size());
	copy (vec.begin(), vec.end()-1, freq_begins.begin()+1);
	for(auto index = 1; index < freq_begins.end(); ++index)
	{
		freq_begins[index] += freq_begins[index-1];
	}
	return freq_begins;
}

template <class T>
void radix_sort(vector<T>& vec)
{
	const size_t radix_count = sizeof(T);
	vector<T> buffer(vec.size());
	
	for(size_t radix = 0; radix < radix_count; ++radix)
	{
		auto freq = compute_freq(vec, radix);
		auto freq_begins = cumulative_sums(freq);
		
		for(auto X : vec)
		{
			auto index_begin = get_radix(X, radix);
			auto index = freq_begins[index_begin];
			buffer[index] = X;
			freq_begins[index_begin]++;
		}
		vec.swap(buffer);
	}
} 