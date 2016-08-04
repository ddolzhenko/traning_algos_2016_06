


namespace SLL {

    template <class T>
    struct Node {
        Node(const T& data_): data(data_), next(nullptr) {}
        T data;
        Node* next;
    };

    template <class T>
    Node<T>* insert_after(Node<T>* who, const T& what) {
        assert(who != nullptr);

        Node<T>* node = new Node<T>(what);
        node->next = who->next;
        who->next = node;
    }




}


namespace DLL {
 
    struct Node {
        Node(Node<T>* prev_=nullptr, Node<T>* next_=nullptr)
        : prev(prev_) 
        , next(next_)
        {}

        #ifndef NDEBUG
            vitrual void DUMMY_DDDDDDDverhkvuioerovued() {};
        #endif

        Node* next;
        Node* prev;
    };

    template <class T>
    struct DataNode : public Node {
        DataNode(const T& data_)
        : Node()
        , data(data_)
        {}

        T data;
    };

    Node* insert_before(Node* where, Node* what) {
        assert(where != nullptr && where->prev != nullptr);
        
        what->prev = where->prev;
        what->next = where;
        where->prev->next = what;
        where->prev = what;

        return what;
    }

    Node* cut(Node* what) {
        assert(what != nullptr);

        Node* next = what->next;
        Node* prev = what->prev;
        prev->next = next;
        next->prev = prev;
        return next;
    }
   
}

template <class T>
struct ListIterator : std::iterator<T, std::bidirectional_iterator_tag>
{
public:
    typedef std::size_t         size_type;
    typedef T                   value_type;
    typedef T&                  reference;
    typedef const T&            const_reference;
    typedef T*                  pointer;
    typedef const T*            const_pointer;
    typedef std::iterator<T>    difference_type;
    
    ListIterator():m_node(nullptr) {}
    ListIterator(const ListIterator&) = default;
    ListIterator(ListIterator&&) = default;

    ListIterator& operator=(const ListIterator&) = default;
    ListIterator& operator=(ListIterator&&) = default;

    ~ListIterator() = default;


public: // navigation

    ListIterator& operator++() {
        m_node = m_node->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator result = *this;
        m_node = m_node->next;
        return result;
    }

    ListIterator& operator--() {
        m_node = m_node->prev;
        return *this;
    }

    ListIterator operator--(int) {
        ListIterator result = *this;
        m_node = m_node->prev;
        return result;
    }

public:

    reference operator*() {
        assert(dynamic_cast<DataNode<T>>(m_node) != nullptr);
        return static_cast<DataNode<T>>(m_node)->data;
    }

    pointer operator->() {
        return &(this->operator*());
    }

private:
    friend class List<T>;

    bool is_valid() const {
        return m_node != nullptr;
    }

    ListIterator(Node* node)
    : m_node(node)
    {}


    Node* m_node;
};


template <class T>
class List
{
public: // types

    typedef std::size_t     size_type;
    typedef T               value_type;
    typedef T&              reference;
    typedef const T&        const_reference; 
    typedef ListIterator<T> iterator;
    typedef const iterator  const_iterator;

public: // ctors
    List()
    : m_dummy(&m_dummy, &m_dummy)
    , m_size(0)
    {}

    List(const List& rhs)
    :List()
    {
        for(const auto& x : rhs)
            this->push_back(x);
    }

    template <class TIter>
    List(TIter b, Titer e)
    : List()
    {
        for (auto it = b, it != e; ++it) {
            push_back(*it);
        }
    }

    List(List&& rhs) = default;

    List<T>& operator=(const List<T>& rhs) {
        if(this != &rhs)
        {
            List<T> tmp(rhs);
            this->swap(tmp);
        }
        return this;
    }

    List<T>& operator=(List<T>&& rhs) = default;

    ~List() {
        while(!empty()) {
            pop_back();
        }
    }

    void swap(List<T>& other) {
        std::swap(m_dummy, other.m_dummy);
        std::swap(m_size, other.m_size);
    }

    template <class TIter>
    List& assign(TIter b, TIter e) {
        List<T> tmp(b, e);
        swap(tmp);
        return *this;
    }

public: // container state

    size_type size() const  { return m_size; }
    bool empty() const      { return size() == 0; }


public: // iterators
    iterator begin()        { return ++iterator(&m_dummy); }
    iterator end()          { return iterator(&m_dummy); }

    reference front()       { return *begin(); }
    reference back()        { return *(--end()); }

public: // modifiers

    void push_front(const_reference x) {
        assert(validate_invariant());

        insert(begin(), x);

        assert(validate_invariant());
    }

    void push_back(const_reference x) {
        assert(validate_invariant());

        insert(end(), x);

        assert(validate_invariant());
    }

    iterator insert(iterator where, const_reference x) {
        assert(validate_invariant());
        
        auto result = DLL:insert_before(where.m_node, new DataNode<T>(x));
        ++m_size;

        assert(validate_invariant());
        return result;
    }

    iterator erase(iterator where) {
        assert(validate_invariant());

        auto result = iterator(DLL::cut(where.m_node));
        
        assert(where.m_node != &m_dummy);
        delete static_cast<DataNode<T>>(where.m_node);

        assert(validate_invariant());
        return result;
    }


private:

   
    bool validate_pointers() const {
        auto ptr = &m_dummy;
        while(ptr->next != m_dummy) {
            if(ptr->next->prev != ptr)
                return false;
            ptr = ptr->next;
        }
        return true;
    }

    bool validate_size() const {
        size_type size = 0;
        for(auto it = begin(); it != end(); ++ it) {
            size++;
        }
        return size == m_size;
    }
    
    bool validate_invariant() const {
        return validate_pointers() && validate_size();
    }

    Node        m_dummy; 
    size_type   m_size;
};