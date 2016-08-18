#include "Header.h"
#include <list>


template <class TKey, class TValue, class THasher>
class hash_map
{
public:
	typedef size_t size_type;
	typedef TKey key_type;
	typedef std::pair<TKey, TValue> value_type;
	typedef value_type& reference;

	typedef THasher hash_type;

	typedef hash_map<TKey, TValue, THasher> self_type;

	typedef std::forward<list<value_type> > bucket_type;
	typedef std::vector<bucket_type> storage_type;

public:
	hash_map(size_type bucket_count=64, hash_type hasher=hash_type())
		:m_buckets(bucket_count, bucket_type())
		, m_hasher(hasher)
	{}

	~hash_map() = default;

	hash_map(const self_type&) = default;
	hash_map(const self_type&&) = default;
	self_type& operator=(const self_type&) = default;
	self_type& operator=(self_type&&) = default;

	void swap(self_type& rhs)
	{
		std::swap(m_buckets, rhs.m_buckets);
		std::swap(m_hasher, rhs.m_hasher);
	}

	class iterator
	{
	public:
		typedef bucket_type::iterator bucket_iterator;
		typedef storage_type::iterator storage_iterator;
		
		iterator(storage_iterator si, storage_iterator se, bucket_iterator bi = bucket_iterator())
			: m_bucket(si)
			, m_elem(bi)
			, m_bucket_end(se)
		{
			fix_forward();
		}

		bool operator==(const iterator& other)
		{
			assert(this->m_bucket_end == other.m_bucket_end);
			if (this->m_bucket != other.m_bucket)
				return false;
			if (this->m_bucket == m_bucket_end)
				return true;

			return this->m_elem == other.m_elem;
		}
		iterator& operator++()
		{
			assert(m_elem != m_bucket->end());
			++m_elem;
			fix_forward();
			return *this;
		}

		iterator& operator--()
		{}

		value_type* operator->()
		{
			return &(*m_elem);
		}

		reference operator*()
		{
			return *this->operator->();
		}

		void fix_forward()
		{
			//assert(m_bucket != m_bucket_end);

			auto not_valid_pos = [this]() {
				return m.elem == m_bucket.end();
			}

			auto valid_bucket = [this]() {
				//return m.elem == m_bucket.end();  ??
			}

			while(valid_bucket() && not_valid_pos())
			{
				++m_bucket;
				m_elem = m_bucket.begin();
			}
		}
			
		bucket_type::iterator m_elem;
		storage_type::iterator m_bucket;
		storage_type::iterator m_bucket_end;
	};
public:

	iterator find(const key_type& key)
	{
		auto bucket_index = hash(key);
		auto bucket = m_buckets.begin() + bucket_index;

		bucket_type::iterator elem = 
			std::find_if(bucket->begin(), bucket->end(),
			[&key](const key_type& k) {
			return key == k;
		});
		return iterator(bucket, elem);
	}

	iterator insert(const value_type& x)
	{
		auto bucket = m_buckets.begin() + hash(x.first);
		bucket.push_front(x);
		return iterator(bucket, bucket.begin());
	}

	iterator erase(iterator it)
	{
		auto new_pos = it.m_bucket.erase(it.m_elem);
		return iterator(it.m_bucket, new_pos);
	}

	iterator remove(const key_type& x)
	{
		return erase(find(x));
	}

	value_type& operator[](const key_type& key)
	{
		auto it = find(key);
		if (it == end())
		{
			it = insert(key, TValue());
		}
		return *it;
	}

	iterator begin()
	{
		return iterator(m_buckets.begin, m_buckets.begin()->begin());
	}
	

private:

	size_type hash(const key_type& key)
	{
		return m_hasher(key) % m_buckets.size();
	}

	storage_type m_buckets;
	hash_type m_hasher;
}; 
