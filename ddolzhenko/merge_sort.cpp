



void merge(b, m, e, out_begin) {
    auto out_end = out_begin;
    auto i = b;
    auto j = m;
    while(i < m && j < e) {
        assert(is_sorted(out_begin, out_end));
        if(*i < *j) {
            *out_end = *i++;
        } else {
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


extern  void foo();

void merge_sort(b, e, buff) {
    // assert(e >= b);
    if(e-b > 1) {
        // [b, e) = [b, m) U [m, e)
        auto m = b + (e-b)/2;
        merge_sort(b, m, buff);
        merge_sort(m, e, buff);
        merge(b, m, e, buff);
        copy(buff, buff+(e-b), b);
    }

    assert(is_sorted(b, e));
}


void foo(int a, int b)
{

}



template <class T>
void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <class T> void swap(std::vector<T>& x, std::vector<T>& y)
{
    x.swap(y);
}


void merge_sort_helper(std::vector<T>& v, std::vector<T>& buff)
{
    if(v.size() < 2)
        return;

    auto m = v.size()/2;
    merge_sort(b, m, buff);
    merge_sort(m, e, buff);

    merge(b,m,e, buff.begin());

    swap(v, buff);
}

template <class T>
class vector
{
public:
    vector(size_t size = 0)
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
    {
        m_data = new T[size];
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

    vector<T>& operator=(const vector<T>& other)
    {
        if(this != &other)
            this->swap(vector<T>(other));
    }

    ~vector() {
        delete [] m_data;
    }

    void swap(vector<T>& other) {   // nothrow
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    void reserve(size_t new_size) {
        if(m_capacity < new_size) {
            T* tmp = new T[new_size];
            copy(begin(), end(), tmp);
            delete [] m_data;
            m_data = tmp;
            m_capacity = new_size;
        }
    }
    
public:
    T& operator[]       (size_t index)       { return m_data[index] }
    const T& operator[] (size_t index) const { return m_data[index] }

    T* begin()  { return m_data; }
    T* end()    { return m_data+m_size; }



    void push_back(const T& x) {
        assert(m_capacity >= m_size);

        if(m_capacity == m_size) {
            reserve(m_size*2);
        }
        
        *(end()) = x;
        m_size++;
    }

    

private:
    T*      m_data;
    size_t  m_size;
    size_t  m_capacity;
};

void merge_sort_2(std::vector<T>& v)
{
    std::vector<T> buff(v.size());
    merge_sort_helper(v, buff);
}