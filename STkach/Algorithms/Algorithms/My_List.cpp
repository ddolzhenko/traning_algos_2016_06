
#include <cassert>

namespace SLL
{
	template<class T>
	struct Node
	{
		Node(const T& data_) : data(data_), next(nullptr) {}

		T data;
		Node* next;
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
		Node() : next(nullptr), prev(nullptr) {}
		Node* next;
		Node* prev;
	};

	template<class T>
	struct DataNode : public Node
	{
		DataNode(const T& data_)
			: Node()
			, data(data_)
		{}

		T data;
	};

	template <class T>
	Node* insert_before(Node* who, Node<T>* what)
	{
		assert(who != nullptr);
		
		what->prev = who->prev;
		what->next = who;
		
		who->prev->next = node;
		who->prev = node;

		return node;
	}

	template <class T>
	Node<T>* insert_after(Node<T>* who, const T& what)
	{
		assert(who != nullptr);
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
}

template<class T>
struct ListIterator 
{
public:
	typedef std::size_t		size_type;
	typedef T				value_type;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef std::iterator<T> difference_type;
	typedef const T*		const_pointer;
	typedef std::iterator<T> difference_type;

	ListIterator() : m_node(nullptr) {}
	ListIterator(const ListIterator&) = default;
	ListIterator(ListIterator&&) = default;

	ListIterator& operator=(const ListIterator&) = default;
	ListIterator& operator=(ListIterator&&) = default;

	ListIterator() = default;

public:
	reference operator*()
	{
		assert(dynamic_cast<DataNode<T>(m_node) != nullptr);
		return &static_cast<DataNode<T>>(m_node)->data;
	}

	pointer operator->()
	{
		return &(*this);
	}

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
	ListIterator


};

template<class T>
class List
{ 
public:  // types


	List()
		: m_dummy()
		, m_size(0)
	{
		m_dummy.next = &m_dummy;
		m_dummy.prev = &m_dummy;
	}

	List(const List& rhs)
		: List()
	{
		for (const auto& x : rhs)
			this->push_back(x);
	}



	List(List&& rhs) = default;

	List<T>& operator=(const List<T>& rhs)
	{
		if (this != &rhs)
		{
			List<T> tmp(rhs);
			this->swap(tmp);
		}
		return this;
	}

	List<T>& operator=(const List<T>& rhs) = default;

	~List()
	{
		while (!empty()) {
			pop_back();
		}
	}

	void swap(List<T>& other)
	{
		std::swap(m_dummy, other.m_dummy);
		std::swap(m_size, other.m_size);
	}

	template<class TIter>
	List& assign(TIter b, TIter e)
	{
		List<T> tmp(b, e);
		swap(tmp);
		return *this;

	}

public:
	size_type size() const	{ return m_size; }
	bool empty() const		{ return size() == 0; }

public: //iterators
	iterator begin() { return ++iterator(&m_dummy); }
	iterator end()   { return iterator(&m_dummy); }

	reference front()	{ return *begin(); }
	reference back()	{ return *(--end()); }

public: // modifiers
	void push_front(const_reference x)
	{
		assert(validate_invariant());

		auto node = DataNode<T>(x);
		DLL::insert_after(m_dummy, node);
		++m_size;
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
		auto result = DLL::insert_before(where.m_node, new DataNode<T>(x));
		++m_size;

		return result;
	}

	iterator erase(iterator where)
	{
		assert(validate_invariant());
		auto result = iterator(DLL::cut(where.m_node));

		assert(where.m_node != m_dummy);
		delete static_cast<DataNode<T>>(where.m_node);

		assert(validate_invariant());
		return result;
	}
private:
	/*bool validate_head_tail() const {
		bool head_ok =  m_head == nullptr || m_head->prev == nullptr;
		bool tail_ok = m_tail == nullptr || m_tail->next == nullptr;
		bool both_ok = !((m_tail == nullptr) ^ (m_head == nullptr))
		return head_ok && tail_ok && both_ok;
	}
	*/
	bool validate_pointers() const	{
		auto ptr = &m_dummy;

			while (ptr->next != m_dummy) {
				if (ptr->next->prev != ptr)
					return false;
				ptr = ptr->next;
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

	bool validate_invariant() const {
		return
			validate_pointers() &&
			validate_head_tail() &&
			validate_size() &&
	}

	Node m_dummy;
	size_type m_size;


};