
class vector
{
public:
	vector(size_t size = 0)
	{
		m_data = new T[size];
		m_size = size;
	}

	vector(const vector<T>& other)
	{
		m_data = new T[other.size()];
		m_size = other.size();
		std::copy(other.begin(), other.end(), m_data);
	}

	`vector()
	{
		delete [] m_data ;
	}

	verctor<T>& operator=(const vector<T>& other)
	{
		if (this != other)
			this->swap(vector<T>(other));
	}

	T& operator[](size_t index)
	{
		return m_data[index];
	}

	T* begin() {return m_data;}
	T* end() {return m_data+m_size;}

	void swap(vector<T>& other) // nothrow
	{

	}

	void push_back(const T& x)
	{
		
	}

private:
	T* m_data;
	size_t m_size;
}

void merge(b, m, e, out_begin)
{
	auto out_end = out_begin;
	auto i = b;
	auto j = m;
	while(i < m && j < e)
	{
		assert(is_sorted(out_begin, out_end));
		if (*i < *j)
		{
			*out_end = *i++;
		}
		else
		{
			*out_end = *j++;
		}
		out_end++;
		assert(is_sorted(out_begin, out_end));
	}
	
	out_end = copy(i, m, out_end);
	out_end = copy(j, e, out_end);

	assert(is_sorted(out_begin, out_end));
	assert(out_end - out_begin == e - b);
}

void merge_sort(b,e, buff)
{
	if (e-b > 1)
	{
		// [b,e) = [b,m) U [m,e)
		auto m = b + (e - b)/2;

		merge_sort(b,m, buff);
		merge_sort(m,e, buff);
		merge(b, m, e, buff);
		copy(buff, buff+(e-b), b);
	}

}

void merge_sort_helper(std::vector<T>& v, std::vector<T>& buff)
{
	if(v.size() < 2)
		return;

	auto m = v.size()/2;
}

void merge_sort2(std::vector<T>& v)
{
	std::vector<T> buff(v.size());
	merge_sort_helper(v, buff);
}