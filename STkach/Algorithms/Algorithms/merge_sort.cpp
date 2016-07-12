#include <cassert>
#include <vector>

//using namespace std;

template<class TIter>
void merge(TIter begin, TIter m, TIter end, TIter out_begin)
{
	auto out_end = out_begin;
	auto i = begin;
	auto j = m;
	while ((i < m) || (j < e))
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

	out_end = copy(j, m, out_end);
	out_end = copy(j, e, out_end);

	assert(is_sorted(out_begin, out_end));
	assert(out_end - out_begin == end - begin)
}


template<class TIter>
void merge_sort(TIter begin, TIter end, TIter buffer)
{
	if (end - begin > 1)
	{
		// [begin, end) = [begin, m) U [m, end)
		auto m = begin + (end - begin) / 2;
		merge_sort(begin, m, buffer);
		merge_sort(m, end, buffer);
		merge(begin, m, end, buffer);

		copy(buffer, buffer + (end - begin), begin);	
	}
}

void merge_sort_helper(vector<T>& v, vector<T>& buffer)
{
	if (v.size() < 2)
	{
		return;
	}

	auto m = v.size() / 2;
	merge_sort(b, m, buffer);
	merge_sort(m, e, buffer);


}

void merge_sort_2(vector<T>& v)
{
	vector<T> buff(v.size());
	merge_sort_helper(v, buffer);
}

template<class T>
class vector {
public:
	vector(size_t size = 0)
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
	{
		m_size = size;
		m_capacity = m_size;
	}
	vector(const vector<T>& other)
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
	{
		m_data = new T[other.size()];
		m_size = other.size();
		m_capacity = m_size;
		std::copy(other.begin(), other.end(), m_data);
	}

	vector<T>& operator=(const vector<T> &other)
	{
		if (this != &other)
		{
			this->swap(vector<T>(other));
		}
	}

public:

	T& operator[](size_t index)
	{
		return m_data[index];
	}
	const T& operator[](size_t index) const
	{
		return m_data[index];
	}

	T* begin() {
		return m_data;
	}

	T* end() {
		return m_data + m_size;
	}

	void push_back(const T& x) 
	{
		assert(m_capacity >= m_size);
		if (m_capacity == new_size)
		{
			reserve(m_size * 2);
		}
	
		*(end()) = x;
		m_size++;
	}

	void reserve(size_t new_size)
	{
		if (m_capacity < new_size)
		{
			T* tmp = new T[new_size];
			copy(begin(), end(), tmp);
			delete []m_data;
			m_data = tmp;
			m_capacity = new_size;
		}
	}

	void swap(vector<T>& other)
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
	}

private:
	T*		m_data;
	size_t	m_size;
	size_t  m_capacity;
};