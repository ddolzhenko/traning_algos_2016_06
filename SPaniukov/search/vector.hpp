template <class T>
class vector
{
public:
    
    vector(size_t size = 0)
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
    {
        m_data = new T(size);
        m_size = size;
    }

    vector(const vector<T> other)
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
    {
        m_data = new T[other.size()];
        m_size = other.m_size();
        copy(other.begin(), other.end(), m_data);
    }
    
    ~vector()
    {
        delete[] m_data;
    }

    void swap(vector<T>& other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

public:
    
    vector<T>& operator=(const vector<T>& other)
    {
        if (this != &other)
            this->swap(vector<T>(other));
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }

    *T begin()
    {
        return m_data;
    }

    *T end()
    {
        return m_data + m_size;
    }

    const *T begin()
    {
        return const m_data;
    }

    const *T end()
    {
        return const m_data + m_size;
    }

    void push_back(const T& x)
    {
        if (m_capacity == m_size)
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
            delete[] m_data;
            m_data = tmp;
            m_capacity = new_size;
        }

    }

private:
    *T m_data;
    size_t m_size;
    site_t, m_capacity;

};