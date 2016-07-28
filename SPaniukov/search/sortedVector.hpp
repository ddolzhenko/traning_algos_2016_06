#ifndef SORTED_VECTOR_HPP
#define SORTED_VECTOR_HPP
#include <vector>
#include <cassert>

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

	CSortedVector() = default {}
	
	template<class TIter>
	CSortedVector(TIter first, TIter last) 
		: m_data(first, last)
	{
		sort(m_data.begin(), m_data.end());
		assert(validate_invariant());
	}

	CSortedVector(const CSortedVector<T>&) = default {}
	CSortedVector(const CSortedVector<T>&&) = default {}

	CSortedVector& operator= (const CSortedVector<T>&) = default;
	CSortedVector& operator= (const CSortedVector<T>&&) = default;

	void swap(CSortedVector<T>& rhs)
	{
		m_data.swap(rhs.m_data);
		assert(validate_invariant());
	}

	~CSortedVector() = default {}

public: //global modifiers

	void reserve(size_type new_size) { m_data.reserve(new_size);  }
	void clean() { m_data.clean(); }

	template<class TIter>
	const CSortedVector& assign(TIter first, TIter last)
	{
		this->swap(CSortedVector<T>(first, last));
		return *this;
	}

public: //state
	size_type size() const { m_data.size()}
	bool empty() const { m_data.empty(); }

public://iterators

	const_iterator begin() const { return m_data.begin(); }
	const_iterator end() const { return m_data.end(); }

public://accessors

	const_reference min() const { return m_data.front(); }
	const_reference max() const { return m_data.back(); }
	const_reference median() const {	return *((begin() + end() - begin()) / 2);}
	const_iterator find(const_reference x) const 
	{
		auto lb = lower_bound(begin(), end(), x);
		if (lb != ned() && !(*lb > x))
		{
			return lb;
		}
		return end();
	}


public: //modifiers

	const_iterator add(const_reference x)
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
	
	const_iterator erase(const_reference x)
	{
		assert(validate_invariant());

		auto it = find(x);
		if(it!= end())	it = erase(it);

		assert(validate_invariant());
		return it;
	}

	const_iterator erase(const_iterator it)
	{
		assert(validate_invariant());
		auto result = m_data.erase(it);
		assert(validate_invariant());
		return result;
	}

private:
	void validate_invariant() const
	{
		return is_sorted(m_data.begin(), m_data.end());
	}


private:
	data_impl m_data;

};

#endif