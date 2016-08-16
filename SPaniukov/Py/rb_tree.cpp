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

	bool m_black;
	Node* left;
	Node* right;
	Node* m_parent;
	T data;
}

Node<T>* min_node(Node<T>* left, Node<T>* right)
{
	if (is_nil(left)) return right;
	if (is_nil(right)) return left;
	return left->data < right->data ? left : right;
}

Node<T>* max_node(Node<T>* left, Node<T>* right)
{
	if (is_nil(left)) return right;
	if (is_nil(right)) return left;
	return left->data < right->data ? right : left;
}

bool is_red(Node<T>* node) const
{
	return !is_black(node);
}
	
bool is_black(Node<T>* node) const
{
	return is_nil(node) || node->m_black;
}

bool is_nil(Node<T>* node) const
{
	return node == nullptr;
}

bool is_real(Node<T>* node)
{
	return !is_nil(node);
}

NodeBase nil;

bool is_nil(NodeBase* node)
{
	return node == &nil;
}

Node<T>* max_element(Node<T>* node)
{
	if(is_real(node)) 
	{
	 node = max_node(node, max_element(node->left));
     node = max_node(node, max_element(node->right));
	}

	return node;
}

Node<T>* min_element(Node<T>* node)
{
	if(is_real(node)) 
	{
	 node = min_node(node, min_element(node->left));
     node = min_node(node, min_element(node->right));
	}

	return node;
}


bool is_bst(NodeBase* node)
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

NodeBase* max_node(NodeBase* node)
{
	if(is_nil(node))
	{
		return node;
	}

	while(is_nil(node->right))
	{
		node = node->right;
	}
	return node;
}

Node<T>* find(Node<T>* node, const &T x)
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

Node<T>* insert_bst((Node*)& node, Node* what)
{
	assert(is_bst(node) && is_real(what));

	if (is_nil(node))
	{
		//what->m_parent = node;
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

size_t black_hieght(Node* node)
{
	if (is_nil(node)) return 0;

	size_t h  = is_black(node) ? 1 : 0;
	return h + std::max(black_hieght (node->left), black_hieght(node->right));
}

bool is_rbtree(Node* node)
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

bool is_root(Node* node)
{
	return is_nil(node->m_parent);
}

void fix_insert_rbtree(Node* node)
{

}


void insert_rbtree(Node* node, Node* what)
{
	assert (is_rbtree(node) && is_real(what));

	auto pos = insert_bst(node, what);
	assert (is_real(pos));
	if(is_root(node))
		return;

	auto dad = node->m_parent;
	if (is_black(dad)) return;

	if (is_root(dad))
	{
		dad->m_black = true;
	}
	
	auto grandpa = dad->m_parent;
	auto uncle = dad == grandpa->left ? right : left;

	if(is_red(uncle))
	{
		grandpa->flip();
		dad->flip();
		uncle->flip();
		return insert_rbtree();
	}
}
