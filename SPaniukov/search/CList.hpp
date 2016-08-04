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
		Node(Node* next_ = nullptr, Node* prev_ = nullptr)
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

	Node* insert_before(Node* where, Node* what)
	{
		//assert(where != nullptr && where->prev != nullptr);

		if (where->next == nullptr && where->prev == nullptr)
		{
			what->next = where;
			what->prev = where;
			where->prev = what;
			where->next = what;
		}
		else
		{
			what->next = where;
			what->prev = where->prev;
			where->prev->next = what;
			where->prev = what;
		}
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
	struct ListIterator
	{
	public: // types

		typedef std::size_t         size_type;
		typedef T                   value_type;
		typedef T&                  reference;
		typedef const T&            const_reference;
		typedef T*                  pointer;
		typedef const T*            const_pointer;
		//typedef std::iterator<T>    difference_iterator;

	public:

		ListIterator()
			: m_node(nullptr)
		{}

		ListIterator(const ListIterator<T>&) = default;
		ListIterator(ListIterator<T>&&) = default;
		
		ListIterator& operator=(const ListIterator<T>&) = default;
		ListIterator& operator=(ListIterator<T>&&) = default;
		
		~ListIterator() = default;

	public:

		ListIterator<T>& operator++()
		{
			m_node = m_node->next;
			return *this;
		}

		ListIterator<T>& operator++(int)
		{
			ListIterator<T> result = *this;
			m_node = m_node->next;
			return result;
		}

		ListIterator<T>& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}

		ListIterator<T>& operator--(int)
		{
			ListIterator<T> result = *this;
			m_node = m_node->prev;
			return result;
		}

	public:

		reference operator*()
		{
			//assert(dynamic_cast<DataNode<T>*>(m_node) != nullptr);
			return static_cast<DataNode<T>*>(m_node)->data;
		}

		pointer operator->()
		{
			return &(this->operator*());
		}
		
		const Node* getNode() const
		{
			return m_node;
		}
	
	private:

		template <class T>
		friend class CList;

		ListIterator(Node* node)
			: m_node(node)
		{}
		
		bool is_valid() const
		{
			return m_node == nullptr;
		}

		Node* m_node;
	};

	template<class T>
	bool operator!=(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
	{
		return !(lhs.getNode() == rhs.getNode());
	}

	template<class T>
	bool operator==(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
	{
		return lhs.getNode() == rhs.getNode();
	}

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
			: m_dummy()
			, m_size(0)
		{}

		template <class TIter>
		CList(TIter begin, TIter end)
			: CList()
		{
			for (auto it = begin; it != end; it++)
			{
				push_back(*it);
			}
		}

		CList(CList<T>& rhs)
			: CList()
		{
			for (auto it = rhs.begin(); it != rhs.end(); it++)
			{
				push_back(*it);
			}
		}

		CList(const CList<T>&& rhs) 
			: CList()
		{
			for (const auto& x : rhs)
			{
				push_back(x);
			}
		}

		CList<T>& operator=(CList<T>& rhs)
		{
			if (this != &rhs)
			{
				CList<T> tmp = CList<T>(rhs);
				this->swap(tmp);
			}
			return *this;
		}

		CList<T>& operator=(const CList<T>&& rhs) 
		{
			if (this != &rhs)
			{
				CList<T> tmp(rhs);
				this->swap(tmp);
			}
			return *this;
		}

		~CList() 
		{
			while (!empty())
			{
				pop_back();
			}
		}
		
		void swap(CList<T>& other)
		{
			//std::swap(m_dummy, other.getDummy());
			//std::swap(m_size, other.getSize());
			Node tmp_dummy = other.getDummy();
			size_type tmp_size = other.getSize();
			other.setDummy(this->getDummy());
			other.setSize(this->getSize());
			this->setDummy(tmp_dummy);
			this->setSize(tmp_size);
		}

		template <class TIter>
		CList<T>& assign(TIter begin, TIter end)
		{
			CList<T> tmp(begin, end);
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
			insert(end(), x);
		}
		
		iterator insert(iterator where, const_reference x)
		{
			assert(validate_invariant());

			auto result = DLL::insert_before(where.m_node, new DataNode<T>(x));
			++m_size;
			assert(validate_invariant());
			return iterator(result);
		}

		iterator erase(iterator where)
		{
			assert(validate_invariant());

			auto result = iterator(DLL::cut(where.m_node));

			assert(where.m_node != &m_dummy);
			
			delete static_cast<DataNode<T>*>(where.m_node);
			--m_size;

			assert(validate_invariant());
			return result;
		}

		iterator pop_back()
		{
			auto it = end();
			return erase(--it);
		}

		void splice(iterator where, CList<T>& list)
		{
			auto my_it = where;
			for (auto it = list.begin(); it != list.end(); it++)
			{
				insert(my_it, *it);
			}
		}

		void reverse()
		{
			CList<T> tmp = CList<T>();
			for (auto it = --end(); it != end(); it--)
			{
				tmp.push_back(*it);
			}
			swap(tmp);
		}

		Node& getDummy()
		{
			return m_dummy;
		}

		void setDummy(Node& dummy)
		{
			m_dummy = dummy;
		}

		size_type& getSize()
		{
			return m_size;
		}

		void setSize(size_type& size)
		{
			m_size = size;
		}
		
	private:
		
		bool validate_size() 
		{
			if (m_dummy.next != m_dummy.prev)
			{
				size_type size = 0;
				for (auto it = begin(); it != end(); ++it)
				{
					size++;
				}
				return size == m_size;
			}
			return true;
		}
		
		bool validate_pointers() 
		{
			if (m_dummy.next != m_dummy.prev)
			{
				auto ptr = &m_dummy;
				while (ptr->next != &m_dummy)
				{
					if (ptr->next->prev != ptr)
						return false;
					ptr = ptr->next;
				}
			}
			return true;
		}

		bool validate_invariant() 
		{
			return validate_size() && validate_pointers();
		}
		
		Node       m_dummy;
		size_type  m_size;
	};
}

#endif
