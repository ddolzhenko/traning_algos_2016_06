

template <class T>
class SortedVector {
public:
    typedef std::vector<T> data_impl;

    typedef typename data_impl::size_type       size_type;
    typedef typename data_impl::value_type      value_type;
    typedef typename data_impl::const_reference const_reference;
    typedef typename data_impl::const_iterator  const_iterator;

public: // constructors
    
    SortedVector() = default;

    template <class TIter> SortedVector(TIter first, TIter last) 
    : m_data(first, last) {
        std::sort(m_data.begin(), m_data.end());

        assert(validate_invariant());
    }

    SortedVector(const SortedVector<T>&) = default;
    SortedVector(const SortedVector<T>&&) = default;
    
    SortedVector<T>& operator=(const SortedVector<T>&) = default;
    SortedVector<T>& operator=(const SortedVector<T>&&) = default;

    void swap(SortedVector<T>& rhs) {
        m_data.swap(rhs.m_data);
        
        assert(validate_invariant());
    }

    ~SortedVector() = default;

public: // global state modifiers
    void reserve(size_type new_size)    { m_data.reserve(new_size); }

    void clean()                        { m_data.clean(); }

    template <class TIter>
    SortedVector& assign(TIter first, TIter last) {
        this->swap(SortedVector<T>(first, last));
        return *this;
    }


public: // state
    
    size_type size const            { return m_data.size(); }
    bool empty() const              { return m_data.empty(); }


public: // iterators
    const_iterator begin() const    { return m_data.begin(); }
    const_iterator end() const      { return m_data.end(); }


public: // accessors

    const_reference min() const     { return m_data.front(); }
    const_reference max() const     { return m_data.back(); }
    const_reference median() const  { return *(begin() + (end()-begin())/2); }

    const_iterator find(const_reference x) const {
        auto lb = std::lower_bound(begin(), end(), x);
        if(lb != end() && !(x < *lb))
            return lb;
        return end();
    }

    
public: // modifiers

    const_iterator insert(const_reference x) {
        assert(validate_invariant());

        // [sorted) [x] [sorted)
        // [b, p  ) [p] [p+1, e)
        m_data.push_back(x);
        auto pivot = m_data.end()-1;
        while(begin() < pivot) {
            assert(is_sorted(begin(), pivot) && is_sorted(pivot, end()));

            auto prev = pivot-1;
            if(*prev > *pivot) {
                std::iter_swap(prev, pivot);
            } else {
                break;
            }
            pivot--;

            assert(is_sorted(begin(), pivot) && is_sorted(pivot, end()));
        }

        assert(validate_invariant());
        return pivot;
    }

    const_iterator erase(const_reference x) {
        assert(validate_invariant());
        
        auto it = find(x);
        if(it != end()) {
            it = erase(it);
        }
        
        assert(validate_invariant());
        return it;    
    }

    const_iterator erase(const_iterator it) {
        assert(validate_invariant());
        
        auto result = m_data.erase(it);
        
        assert(validate_invariant());
        return result;
    }


private:

    bool validate_invariant() const {
        return std::is_sorted(m_data.begin(), m_data.end());
    }

private:
    data_impl m_data;
};