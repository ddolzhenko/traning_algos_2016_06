#include "stdafx.h"

namespace SLL  //single linked list
{
   template <class T>
   struct Node
   {
      Node(const T& data_) : data(data_), next(nullptr) {}
      T     data;
      Node* next;
   };

   template <class T>
   Node<T>* insert_after(Node<T>* who, const T& what)
   {
      assert(who != nullptr);
      Node<T>* node = new Node<T>(what);
      node->next = who->next;
      who->next = node;
      return node;
   }
}

namespace DLL  //double linked list
{
   struct Node
   {
      Node(Node* prev_ = nullptr, Node* next_ = nullptr)
         : prev(prev_)
         , next(next_)
      {
      }

      Node* next;
      Node* prev;
   };

   template <class T>
   struct DataNode : public Node
   {
      DataNode(const T& data_)
         : Node()
         , data(data_)
      {}
      T data;
   };

   Node* insert_before(Node* where, Node* what)
   {
      assert(where != nullptr && where->prev != nullptr);

      what->prev = where->prev;
      what->next = where;
      where->prev->next = what;
      where->prev = what;

      return what;
   }

   template <class T>
   Node<T>* insert_after(Node<T>* where, const T& what)
   {
      assert(where != nullptr && where->prev != nullptr);

      what->prev = where;
      what->next = where->next;
      where->next->prev = node;
      where->next = node;

      return what;
   }
}

template <class T>
struct ListIterator
{
public:
   //types
   typedef std::size_t     size_type;
   typedef T               value_type;
   typedef T&              reference;
   typedef const T&        const_reference;
   typedef T*              pointer;
   typedef const T*        const_pointer;
   typedef ListIterator<T> iterator;
   typedef const iterator  const_iterator;
   typedef std::iterator<T> difference_type;

   ListIterator() : m_node(nullptr) {}
   ListIterator(const ListIterator&) = default;
   ListIterator(ListIterator&&) = default;

   ListIterator& operator=() = default;

//navigation
   ListIterator& operator ++()
   {
      m_node = m_node->next;
      return *this;
   }

   ListIterator operator ++(int)
   {
      ListIterator result = *this;
      m_node = m_node->next;
      return result;
   }

   ListIterator& operator --()
   {
      m_node = m_node->prev;
      return *this;
   }

   ListIterator operator --(int)
   {
      ListIterator result = *this;
      m_node = m_node->prev;
      return result;
   }

   reference operator*()
   {
      assert(static_cast<DataNode<T>>(m_node) != nullptr)
      return static_cast<DataNode<T>>(m_node)->data;
   }

   pointer operator->()
   {
      //return &(*this);
      return &(this->operator*());
   }

private:
   friend class List<T>;

   ListIterator(Node * node)
      : m_node(node)
   {}
   Node m_node;
};


template <class T>
class List
{
public:
//types
   typedef std::size_t     size_type;
   typedef T               value_type;
   typedef T&              reference;
   typedef const T&        const_reference;
   typedef ListIterator<T> iterator;
   typedef const iterator  const_iterator;

//ctors
   List()
      : m_dummy(&m_dummy, &m_dummy)
      , m_size(0)
   {
   }
   ~List() {}

   //container state
   size_type size() const { return m_size }
   bool empty() const { return m_size == 0 }

   //iterators
   iterator begin() { return iterator(++(&m_dummy)* }
   iterator end() {return iterator(&m_dummy)}

   reference front() { return *begin(); }
   reference back() { return *(--end()); }

//modifiers
   void push_front(const_reference x)
   {
      assert(validate_invariant());

      //auto node = new DataNode<T>(x);
      //DLL::insert_after(m_dummy, node);
      //++m_size;
      insert(begin(), x);

      assert(validate_invariant());
   }

   void push_back(const_reference x)
   {
      assert(validate_invariant());

      //auto node = new DataNode<T>(x);
      //DLL::insert_before(m_dummy, node);
      //++m_size;
      insert(end(), x);

      assert(validate_invariant());
   }


   iterator insert(iterator where, const_reference x)
   {
      assert(validate_invariant());
      auto result = DLL::insert_before(where.m_node, new DataMode<T>(X))
      ++m_size;
      assert(validate_invariant());

      return result;
   }


private:
   //bool validate_head_tail() const
   //{
   //   bool head_ok = m_head == nullptr || m_head->prev == nullptr;
   //   bool tail_ok m_tail == nullptr || m_tail->next == nullptr;
   //   bool both_ok = (!(m_tail == nullptr) ^ m_head == nullptr)
   //      return head_ok && tail_ok && both_ok;
   //}

   bool validate_pointers() const
   {
      auto ptr = &m_dummy;
      while (ptr->next != m_dummy)
      {
         if (ptr->next->prev)
            return false;
         ptr = ptr = ptr->next;
      }
      return true;
   }

   bool validate_size() const
   {
      size_type size = 0;
      for (auto it = begin(); it != end(); ++it)
         ++size;
      return size == m_size
   }


   bool validate_invariant() const
   {
      return
         validate_size() &&
         validate_pointers();
   }
   Node      m_dummy;
   size_type m_size;
};

int main()
{

   return 0;
}

