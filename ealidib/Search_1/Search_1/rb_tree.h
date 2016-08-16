#include "Header.h"

template <class T>
struct Node
{
	Node(const T daya_)
		: left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, m_is_black(false)
		, data(data_)
	{}

	

	virtual bool less(NodeBase* node) const = 0{}
	bool m_is_black;
	Node* left;
	Node* right;
	Node* parent;
	T data;
};
template <class T>
bool is_nil(Node<T>* node) { return node == nullptr; }
template <class T>
bool is_black(Node<T>* node) { return is_nil(node) || node->m_is_black; }
template <class T>
bool is_red(Node<T>* node) { return !is_black(node); }
template <class T>
bool is_real(Node<T>* node) { return !is_nil(node); }
template <class T>
Node<T> * max_node(Node<T> * l, Node<T> * r)
{
	if (is_nil(l))
		return r;
	if (is_nil(r))
		return l;

	return l->data < r->data;
}

//bool operator 
template <class T>
Node<T>* max_element(Node* node)
{
	if (is_nil(node)
		return node;

	auto maxl = max_element(node->left);
	auto maxr = max_element(node->right);
	auto result = node;

	if (maxl->is_real() && result->less(maxl))
		result = maxl;
}
template <class T>
bool is_bst(Node<T>* node)
{
	if (is_nil(node))
		return true;

	auto m = node;
	m = max_node(m, max_element(node->left));
	m = min_node(m, min_element(node->right));
	return m == node && is_bst(node->left) && is_bst(node->right);
}
template <class T>
Node<T>* min_node(Node<T>* node)
{
	assert(is_bst(node));

	if (is_nil(node))
	{
		return node;
	}

	while (!is_nil(node->left))
	{
		node = node->left;
	}
}
template <class T>
Node<T>* max_node(Node<T>* node)
{
	assert(is_bst(node));
	if (is_nil(node))
	{
		return node;
	}

	while (node->right->is_real())
	{
		node = node->right;
	}

	return node;
}

template <class T>
Node<T>* find(Node<T>* node, const T& x)
{
	if (is_nil(node))
		return node;

	if (node->data < x)
		return find(node->right, x);
	else if (node->data > x)
		return find(node->left, x);

	return node;
}

template <class T>
Node<T>* insert_bst(Node<T>*& node, Node<T>* what)
{
	assert(is_bst(node) && is_real(what));

	if (is_nil(node))
	{
		node = what;
		//what->parent  = ???????????
		return node;
	}
		

	if (what->data < node->data)
	{
		return insert(node->left, what);
	}
	else if(what->data > node->data)
		return insert(node->right, what);

	return node;
}

template <class T>
size_t black_height(Node<T>* node)
{
	if (is_nil(node))
		return 0;

	size_t h = is_black(node) ? 1 : 0;

	return h + std::max(black_height(node->left), black_height(node->right));
}
template <class T>
bool is_brtree(Node<T>* node)
{
	if (is_nil(node))
		return true;
	if (!is_nst(node))
		return false;

	if (is_red(node))
	{
		if (!(node->left->is_black() && node->right->is_black()))
			return false;
	}

	return black_height(node->left) == black_height(node->right);
}

template <class T>
void is_root(Node<T>* node)
{
	return is_nil(node->parent);
}

template <class T>
void fix_insert_rbtree(Node<T>* node)
{
	assert(is_real(node));
	if (is_root(node))
		return;

	auto dad = node->parent;
	if (is_black(dad))
		return;

	if (is_root(dad))
	{
		dad->set_black();
	}

	auto grandpa = dad->parent;
	auto uncle = get_uncle(dad);

	if (is_red(uncle))
	{
		grandpa->flip();
		dad->flip();
		uncle->flip();
		fix_insert_rbtree(grandpa);
	}

	if (dad == grandpa->right)
	{
		auto y = rotate_left(grandpa);
		node->set_black();
		fix_insert_rbtree(pos);
	}
	else
	{
		auto y = rotate_right(grandpa);
		node->set_black();
		fix_insert_rbtree(pos);
	}
}

template <class T>
void insert_rbtree(Node<T>*& node, Node<T>* what)
{
	assert(is_rbtree(node) && is_real(what));
	auto pos = insert_bst(&node, what);
	
	fix_insert_rbtree(pos);
}

template <class TKey, class TValue>
class map
{
public:
	typedef size_t size_type;
	typedef TKey key_type;
	typedef std::pair<TKey, TValue> value_type;
	typedef value_type& reference;

	typedef map<TKey, TValue> self_type;
public:
	map(): root(nullptr) {}

	map(const self_type& rhs)
		:root(nullptr)
	{
		this->assign(rhs.begin(), rhs.end());
	}
private:
	Node<T>* root;
};