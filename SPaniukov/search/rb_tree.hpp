template <class T>
struct Node
{
	Node(const T& data_)
	: m_parent(nullptr)
	, left(nullptr)
	, right(nullptr)
	, m_black(false)
	, data(data_)
	{}

	void set_black() { m_black = true; }

	void flip() { m_black = !m_black; }

	bool m_black;
	Node<T>* left;
	Node<T>* right;
	Node<T>* m_parent;
	T data;
};

template <class T>
bool is_black(Node<T>* node)
{
	return is_nil(node) || node->m_black;
}

template <class T>
bool is_red(Node<T>* node)
{
	return !is_black(node);
}

template <class T>
bool is_nil(Node<T>* node)
{
	return node == nullptr;
}

template <class T>
bool is_real(Node<T>* node)
{
	return !is_nil(node);
}

template <class T>
Node<T>* get_uncle(Node<T>* node)
{
	return node->m_parent->left == node ? node->m_parent->right : node->m_parent->left;
}

template <class T>
Node<T>* min_node(Node<T>* left, Node<T>* right)
{
	if (is_nil(left)) return right;
	if (is_nil(right)) return left;
	return left->data < right->data ? left : right;
}

template <class T>
Node<T>* max_node(Node<T>* left, Node<T>* right)
{
	if (is_nil(left)) return right;
	if (is_nil(right)) return left;
	return left->data < right->data ? right : left;
}

template <class T>
Node<T>* max_element(Node<T>* node)
{
	if(is_real(node)) 
	{
		node = max_node(node, max_element(node->left));
		node = max_node(node, max_element(node->right));
	}

	return node;
}

template <class T>
Node<T>* min_element(Node<T>* node)
{
	if(is_real(node)) 
	{
		node = min_node(node, min_element(node->left));
		node = min_node(node, min_element(node->right));
	}

	return node;
}

template <class T>
bool is_bst(Node<T>* node)
{
	if (is_nil(node))
	{
		return true;
	}

	auto m = node;
	m = max_node(m, max_element(node->left));
	m = min_node(m, min_element(node->right));
	return m == node && is_bst(node->left) && is_bst(node_>right);
}

template <class T>
Node<T>* min_node(Node<T>* node)
{
	assert(is_bst(node));

	if(is_nil(node))
	{
		return node;
	}

	while(is_real(node->left))
	{
		node = node->left;
	}
	return node;
}

template <class T>
Node<T>* max_node(Node<T>* node)
{
	if(is_nil(node))
	{
		return node;
	}

	while(is_real(node->right))
	{
		node = node->right;
	}
	return node;
}

template <class T>
Node<T>* find(Node<T>* node, const T& x)
{
	if (is_nil(node))
	{
		return node;
	}

	if(node->data < x)
	{
		return find(node->right, x);
	}
	else if (x < node->data)
	{
		return find (node->left, x);
	}

	return node;

	/*
	while(is_real(node))
	{
		if (node->data < x) node = node->right;
		else if (x < node->data) node = node->left;
		else break;	
	}
	return node;
	*/
}

template <class T>
Node<T>* insert_bst(Node<T>*& node, Node<T>* what)
{
	assert(is_bst(node) && is_real(what));
	
	what->m_parent = node;
	
	if (is_nil(node))
	{
		node = what;
		return node;
	}

	if (what->data < node->data)
	{
		return insert(node->left, what);
	}
	else if (node->data < what->data)
	{
		return insert(node->right, what);
	}
	return node;
}

template <class T>
size_t black_hieght(Node<T>* node)
{
	if (is_nil(node)) return 0;

	size_t h  = is_black(node) ? 1 : 0;
	return h + std::max(black_hieght (node->left), black_hieght(node->right));
}

template <class T>
bool is_rbtree(Node<T>* node)
{
	if (is_nil(node)) return true;

	if(!is_bst(node)) return false;
	

	if (is_red(node)) 
		{
			if(!(node->left->is_black() && node->right->is_black()))
				return false;
		}

	return black_hieght(node->left) == black_hieght(node->right);
}

template <class T>
bool is_root(Node<T>* node)
{
	return is_nil(node->m_parent);
}

template <class T>
void fix_insert_rbtree(Node<T>* node)
{
	assert(is_real(node));

	if (is_root(node))
		return;

	auto dad = node->m_parent;
	if (is_black(dad))
		return;

	if (is_root(dad)) {
		dad->set_black();
	}

	auto grandpa = dad->m_parent;
	auto uncle = get_uncle(dad);

	if (is_red(uncle)) 
	{
		grandpa->flip();
		dad->flip();
		uncle->flip();
		fix_insert_rb_tree(grandpa);
	}

	auto tmp = dad == grandpa->right ? rotate_left(grandpa) : rotate_right(grandpa);
	node->set_black();
	fix_insert_rb_tree(tmp);
}

template <class T>
void insert_rbtree(Node<T>* node, Node<T>* what)
{
	assert(is_rbtree(node), && is_real(what));
	auto pos = insert_bst(node, what);
	fix_insert_rb_tree(pos);
}
