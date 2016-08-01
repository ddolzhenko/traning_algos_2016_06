#ifndef SORTED_VECTOR_HPP
#define SORTED_VECTOR_HPP
#include <vector>
#include <cassert>
#include <algorithm> 

using namespace std;

template <class T>
class CSortedVector
{
public:
	typedef vector<T> data_impl;
	typedef typename data_impl::size_type size_type;
	typedef typename data_impl::value_type value_type;
	typedef typename data_impl::const_reference const_reference;
	typedef typename data_impl::const_iterator const_iterator;

	CSortedVector();
	
	template <class TIter>
	CSortedVector(TIter first, TIter last);
	
	explicit CSortedVector(const vector<T>& vec);

	CSortedVector(CSortedVector<T>&);
	CSortedVector(const CSortedVector<T>&&);

	CSortedVector& operator= (const CSortedVector<T>&);
	CSortedVector& operator= (const CSortedVector<T>&&);
	T& operator[] (const size_type index);
	vector<T>& getData();
	void swap(CSortedVector<T>& rhs);

	~CSortedVector();

public: //global modifiers

	void reserve(size_type new_size);
	void clean(); 

	template<class TIter>
	const CSortedVector& assign(TIter first, TIter last);

public: //state
	
	size_type size() const; 
	bool empty() const;

public://iterators

	const_iterator begin() const; 
	const_iterator end() const; 

public://accessors

	const_reference min() const; 
	const_reference max() const; 
	const_reference median() const; 
	const_iterator find(const_reference x) const;

public: //modifiers

	const_iterator add(const_reference x);
	const_iterator erase(const_reference x);
	const_iterator erase(const_iterator it);

private:
	
	bool validate_invariant() const;

private:
	
	data_impl m_data;
};

template <class T>
CSortedVector<T>::CSortedVector()
	: m_data(0)
{
}

template <class T>
template <class TIter>
CSortedVector<T>::CSortedVector(TIter first, TIter last) 
	:m_data(first, last)
{
	sort(m_data.begin(), m_data.end());
	assert(validate_invariant());
}

template <class T>
CSortedVector<T>::CSortedVector(const vector<T>& vec)
	: m_data(vec)
{
	sort(m_data.begin(), m_data.end());
	assert(validate_invariant());
}

template <class T>
CSortedVector<T>::CSortedVector(CSortedVector<T>& vec)
{
	m_data = vec.getData();
}

template <class T>
CSortedVector<T>::CSortedVector(const CSortedVector<T>&& vec)
{
	m_data = vec.getData();
}

template <class T>
CSortedVector<T>& CSortedVector<T>::operator= (const CSortedVector<T>& vec)
{
	m_data = vec.getData();
}

template <class T>
CSortedVector<T>& CSortedVector<T>::operator= (const CSortedVector<T>&&)
{
	m_data = vec.getData();
}

template <class T>
T& CSortedVector<T>::operator[] (const size_type index)
{
	return m_data[index];
}

template <class T>
vector<T>& CSortedVector<T>::getData()
{
	return m_data;
}

template <class T>
void CSortedVector<T>::swap(CSortedVector<T>& rhs)
{
	m_data.swap(rhs.getData());
	assert(validate_invariant());
}

template <class T>
CSortedVector<T>::~CSortedVector()
{
}

template <class T>
void CSortedVector<T>::reserve(size_type new_size)
{
	m_data.reserve(new_size);  
}

template <class T>
void CSortedVector<T>::clean()
{
	m_data.clean(); 
}

template <class T>
template<class TIter>
const CSortedVector<T>& CSortedVector<T>::assign(TIter first, TIter last)
{
	this->swap(CSortedVector<T>(first, last));
	return *this;
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::begin() const
{
	return m_data.begin(); 
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::end() const
{
	return m_data.end(); 
}

template <class T>
typename CSortedVector<T>::size_type CSortedVector<T>::size() const
{ 
	return m_data.size(); 
}

template <class T>
bool CSortedVector<T>::empty() const
{
	return m_data.empty(); 
}

template <class T>
typename CSortedVector<T>::const_reference CSortedVector<T>::min() const
{
	return m_data.front(); 
}
	
template <class T>
typename CSortedVector<T>::const_reference CSortedVector<T>::max() const
{
	return m_data.back(); 
}

template <class T>
typename CSortedVector<T>::const_reference CSortedVector<T>::median() const
{
	return *((begin() + end() - begin()) / 2); 
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::find(const_reference x) const
{
	auto lb = lower_bound(begin(), end(), x);
	if (lb != ned() && !(*lb > x))
	{
		return lb;
	}
	return end();
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::add(const_reference x)
{
	assert(validate_invariant());
	m_data.push_back(x);
	auto pivot = m_data.end() - 1;

	while (begin() < pivot)
	{
		assert(is_sorted(begin(), pivot) && is_sorted(pivot, end()));
		auto prev = pivot - 1;
		if (*prev > *pivot)
		{
			iter_swap(prev, pivot);
		}
		else
		{
			break;
		}
		pivot--;
		assert(is_sorted(begin(), pivot) && is_sorted(pivot, end()));
	}

	assert(validate_invariant());
	return pivot;
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::erase(const_reference x)
{
	assert(validate_invariant());

	auto it = find(x);
	if (it != end())	it = erase(it);

	assert(validate_invariant());
	return it;
}

template <class T>
typename CSortedVector<T>::const_iterator CSortedVector<T>::erase(const_iterator it)
{
	assert(validate_invariant());
	auto result = m_data.erase(it);
	assert(validate_invariant());
	return result;
}

template <class T>
bool CSortedVector<T>::validate_invariant() const
{
	return is_sorted(m_data.begin(), m_data.end());
}

#endif