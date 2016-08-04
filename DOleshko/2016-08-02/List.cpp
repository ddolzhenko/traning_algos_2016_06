

namespace SLL {
    template <class T>
    struct Node {
        T       data;
        Node*   next;

        Node(const T& data_): data(data_), next(nullptr) {}
    };


    template <class T>
    insert_after(Node<T>* who, const Node<T>* what) {
        assert(who != nullptr);

        Node<T>* node = new Node<T>(what);

        node->next = who->next;
        who->next = node;
    }

    template <class T>
    delete_after(Node<T>* who) {
        assert(who != nullptr);
    }    
    

}

namespace DLL {
    struct Node {
        Node*   prev;
        Node*   next;

         Node(next_=nullptr, prev_=nullptr): next(next_), prev(prev_) {}
    };

    template <class T>
    struct DataNode : public Node {
        T   data;


    };

    template <class T>
    insert_after(* who, const Node<T>* what) {
        assert(who != nullptr);

        what->next = who->next;
        what->prev = who;

        if (who->next != nullptr)
            who->next->prev = what;

        who->next = what;

        return what;        
    }

    template <class T>
    insert_before(Node<T>* who, const T& what) {
        assert(who != nullptr);

        Node<T>* node = new Node<T>(what, who, who->prev);

        //node->prev = who->prev;
        //node->next = who;

        if (who->prev != nullptr)
            who->prev->next = node;

        who->prev = node;

        return node;        
    }

    template class<T>
    struct ListIterator
    {
    public:
        ListIterator(): m_node(nullptr) {}



    private:
        friend class List<T>;

        bool is_valid const {
            return m_node != nullptr;
        }

    };


    template class<T>
    class List
    {
    public:  //types

        typedef std::size_t       size_type;
        typedef T                 value_type;
        typedef T&                reference;
        typedef const T&          const_reference;
        typedef ListIterator      iterator;
        typedef constListIterator iterator;


    public:
        List(): m_dummy(), m_size(0) {}
        ~List();

    public:  //container state

        size_type size() const      { return m_size; }
        bool empty() const          { return size() == 0; }

    public:  //iterators
        iterator begin()            { return ++iterator(&m_dummy); }
        iterator end()              { return iterator(&m_dummy); }

        reference front()           { return *begin(); }
        reference back()            { return *(--end()); }

    public:  //modifiers
        void push_front(const_reference x) {
            assert(validate_invariant);

            DLL::insert_after(m_dummy, new DataNode<T>(x));
            ++m_size;

            assert(validate_invariant);
        }

        iterator insert(iterator where, const_reference x) {
            assert(validate_invariant);

            auto result = DLL::insert_before(where.m_node, new DataNode<T>(x));
            ++m_size;

            assert(validate_invariant);
            return result;
        }

        void push_front(const_reference x) {
            assert(validate_invariant);

            insert();

            assert(validate_invariant);
        }

        void push_back(const_reference x) {
            assert(validate_invariant);

            insert();

            assert(validate_invariant);
        }

    private:

        bool validate_head_tail() const {
                bool head_ok = m_head == nullptr || m_head->prev == nullptr;
                bool tail_ok = m_head == nullptr || m_tail->next == nullptr;
                bool both_ok = 

                return head_ok && tail_ok && both_ok;
        }

        bool validate_size() const {
            size_type size = 0;
            for (auto it = begin(); it != end; ++it)
                size++;

            return size == m_size;
        }

        bool validate_invariant() const {
            return
                validate_head_tail() &&
                validate_pointers() &&
                validate_size();
        }
        

        Node        m_dummy;
        size_type   m_size;
    };

}

