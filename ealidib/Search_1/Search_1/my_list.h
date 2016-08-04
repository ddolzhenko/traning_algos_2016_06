#include "Header.h"


namespace SLL
{
	template <class T>
	struct Node
	{
		Node(const T& data_): data(data_), next(nullptr) {}
		T data;
		Node *next;
	};

	template <class T>
	Node<T>* insert_after(Node<T>* who, const T& what)
	{
		assert(who != nullptr);
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
			, prev(prev_) {}
		Node *next;
		Node *prev;
	};

	template <class T>
	struct DataNode : bublic Node	
	{
		DataNode(const T& data_)
			: Node()
			, data(data_) {}
		T data;

	};

	template <class T>
	Node* insert_before(Node* who, const &T what)
	{
		assert(who != nullptr);

		Node* node = new Node(what);

		node->prev = who->prev;
		node->next = who;
		if(who->prev != nullptr) 
		{
			who->prev->next = node;
		}
		
		who->prev = node;
	}

	template <class T>
	Node<T>* insert_after(Node<T>* who, const T& what)
	{
		assert(who != nullptr);
		Node<T>* node = new Node<T>(what);
	}
}

template <class T>
struct ListIterator
{
public:
	ListIterator() :m_node(nullptr) {}
	ListIterator(const ListIterator&) = default;
	ListIterator(ListIterator&&) = dafault;

	ListIterator& operator=(const ListIterator&) = default;
	ListIterator& operator=(ListIterator&) = default;

public: // navigation
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

	ListIterator& operator--()
	{
		m_node = m_node->prev;
		return *this;
	}
	ListIterator& operator--(int)
	{
		ListIterator result = *this;
		m_node = m_node->prev;
		return result;
	}
private:
	friend class List<T>;
	bool is_valid() const
	{
		return m_node != nullptr;
	}
};

template <class T>
class List
{
public: //types
	typedef std::size_t		size_type;
	typedef T				value_type;
	typedef T&				reference;
	typedef	const T&		const_reference;
	typedef ListIterator<T>	iterator;
	typedef const iterator	const_iterator;

public: // ctors
	List()
		: m_dummy(nullptr)
		, m_size(0) {}
	~List();

public: // container state

	size_type size() const { return m_size; }
	bool empty() const { return size() == 0; }
public: // iterators
	iterator begin() { return ++iterator(&m_dummy); }
	iterator end() { return iterator(&m_dummy); }

	reference front() { return *begin(); }
	reference back() { return *(--end()); }

public: // modifiers
	void push_front(const_reference x)
	{
		assert(validate_invariant());

		if (m_head == nullptr)
			m_head = m_tail = new Node<T>(x);
		else
			m_head = DLL::insert_before(m_head, x);

		++m_size;
		assert(validate_invariant());
	}

	iterator insert(iterator where, const_reference x)
	{
		Node<T>* result = nullptr;
		if (m_head == nullptr)
			m_head = m_tail = new Node<T>(x);
		else
		{
			result = DLL::insert_before(where, x);
			if (where.m_node == m_head)
				m_head = result;
			if (where.m_node == m_tail)
				m_tail = result;
		}

		++m_size;
		return result;
	}

private:
	bool validate_head_tail() const
	{
		bool head_ok = m_head == nullptr || m_head->prev == nullptr;
		bool tail_ok = m_tail == nullptr || m_tail->prev == nullptr;
		bool both_ok = !((m_tail == nullptr) ^ (m_head == nullptr));

		return head_ok && tail_ok && both_ok;
	}
	bool validate_pointers() const
	{
		if (m_head != nullptr)
		{
			auto ptr = m_head;
			while (ptr->next)
			{
				if (ptr->next->prev != ptr)
					return false;
				ptr = ptr->next;
			}
		}
		return true;
	}
	bool validate_size() const
	{
		size_type size = 0;
		for (auto it = begin(); it != end(); ++it)
		{
			size++;
		}
		return size == m_size;
	}
	bool validate_invariant() const
	{
		return
			validate_head_tail() &&
			validate_pointers &&
			validate_size();
	}

	Node m_dummy;
	size_type m_size;

};