#ifndef SLIST_HPP
#define SLIST_HPP
#include <cassert>

namespace SLL {

	template <class T>
	struct Node
	{
		Node(T& data_) : data(data_) {}
		T data;
		Node* next;
		Node* prev;
	};

	template <class T>
	Node<T>* insert_after(Node<T> who, const T& what)
	{
		Node<T>* node = new Node<T>(what);
		node->next = who->next;
		who->next = node;
	}
}

namespace DLL
{
	struct Node
	{
		Node(Node* prev_ = nullptr, Node* next_ = nullptr)
			: next(next_)
			, prev(prev_)
		{}
		
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

	Node* insert_before(Node* who, Node* what)
	{
		assert(who != nullptr && who->prev != nullptr);

		what->prev = who->prev;
		what->next = who;
		who->prev->next = what;
		who->next = what;
		
		return what;
	}

	Node* cut(Node* what)
	{
		assert(what != nullptr);
		
		Node* next = what->next;
		Node* prev = what->prev;
		prev->next = next;
		next->prev = prev;

		return next;
	}

	template <class T>
	struct ListIterator : public std::iterator
	{
	public: // types

		typedef std::size_t         size_type;
		typedef T                   value_type;
		typedef T&                  reference;
		typedef const T&            const_reference;
		typedef T*                  pointer;
		typedef const T*            const_pointer;
		typedef std::iterator<T>    difference_iterator;

	public:

		ListIterator()
			: m_node(nullptr)
		{}

		ListIterator(const ListIterator&) = default;
		ListIterator(ListIterator&) = default;
		ListIterator(ListIterator&&) = default;
		
		ListIterator& operator=(const ListIterator&) = default;
		ListIterator& operator=(ListIterator&) = default;
		ListIterator& operator=(ListIterator&&) = default;
		~ListIterator() = default;

	public:

		ListIterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}

		ListIterator& operator++(int)
		{
			ListIterator result = *this;
			m_node = m_node->next;
			return result;
		}

		ListIterator& operator--(int)
		{
			ListIterator result = *this;
			m_node = m_node->prev;
			return result;
		}

	public:

		reference operator*()
		{
			asseret(dynamic_cast<DataNode<T>>(m_node) != nullptr);
			return static_cast<DataNode<T>>(m_node)->data;
		}

		pointer operator->()
		{
			return &(this->operator*());
		}

	private:

		friend class CList<T>;
		ListIterator(Node* node)
			: m_node(node)
		{}
		bool is_valid() const
		{
			return m_node == nullptr;
		}

		Node* m_node;
	};

	template <class T>
	class CList
	{
	public: // types

		typedef std::size_t      size_type;
		typedef T                value_type;
		typedef T&               reference;
		typedef const T&         const_reference;
		typedef ListIterator<T>     iterator;
		typedef const iterator   const_iterator;
	
	public: //ctors

		CList()
			: m_dummy(&m_dummy, &m_dummy)
			, m_size(0)
		{}

		template <class TIter>
		CList(TIter begin, TIter end)
		{

		}

		CList(const CList<T>& rhs)
			: CList()
		{
			for (const auto& x : rhs)
			{
				this->push_back(x);
			}
		}

		CList(const CList&& rhs) = default;

		CList<T>& operator=(const CList<T>& rhs)
		{
			if (this != &rhs)
			{
				CList < T tmp(rhs); 
				this->swap(tmp);
			}
			return *this;
		}

		CList<T>& operator=(const CList<T>&& rhs) = default;

		~CList() 
		{
			while (!empty())
			{
				pop_back();
			}
		}
		
		void swap(CList<T>& other)
		{
			std::swap(m_dummy, other.m_dummy);
			std::swap(m_size, other.m_size);
		}

		template <class TIter>
		CList<T>& assign(TIter begin, TIter end)
		{
			CList tmp(begin, end);
			swap(tmp);
			return *this;
		}
	public: //state
		size_type size() const    { return m_size; }
		bool empty() const        { return size()== 0; }
	
	public: //iterators
		iterator begin()          { return ++iterator(&m_dummy); }
		iterator end()            { return iterator(&m_dummy); }
		reference front()         { return *begin(); }
		reference back()          { return *(--end()); }
	
	public://modifiers
		void push_front(const_reference x)
		{
			assert(validate_invariant());

			insert(begin(), x);

			assert(validate_invariant());
		}

		void push_back(const_reference x)
		{
			assert(validate_invariant());

			insert(end(), x);

			assert(validate_invariant());
		}
		
		iterator insert(iterator where, const_reference x)
		{
			assert(validate_invariant());

			auto result = DLL::insert_before(where.m_node, new DataNode<T>(x));
			++m_size;
			return result;

			assert(validate_invariant());
		}

		iterator erase(iterator where)
		{
			assert(validate_invariant());

			auto result = iterator(DLL::cut(where.m_node));

			assert(where.m_node != &m_dummy);

			delete static_cast<DataNode<T>>(where.m_node);

			assert(validate_invariant());
			return result;
		}
		
	private:
		
		bool validate_size() const
		{
			size_type size = 0;
			for (auto it = begin(); it != end(); ++it)
			{
				size++;
			}
			return size == m_size;
		}
		
		bool validate_pointers() const
		{
			auto ptr = &m_dummy;
			while (ptr->next != m_dummy)
			{
				if (ptr->next->prev != ptr)
					return false;
				ptr = ptr->next;
			}
			return true;
		}

		bool validate_invariant() const
		{
			return validate_size() &&	validate_pointers();
		}
		
		Node       m_dummy;
		size_type  m_size;

	};
}
#endif
