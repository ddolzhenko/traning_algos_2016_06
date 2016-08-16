
template <class T>
struct Node {
    Node(const T data_)
    : left(nullptr)
    , right(nullptr)
    , parent(nullptr)
    , m_is_black(false)
    , data(data_)
    {}


    bool m_is_black;
    Node* left;
    Node* right;
    Node* parent;
    T data;
};

bool is_nil(Node<T>* node)  { return node==nullptr; }

bool is_black(Node<T>* node)  { 
    return is_nil(node) || node->m_is_black; 
}

bool is_red(Node<T>* node)  { return !is_black(node); }

bool is_real(Node<T>* node)  {return !is_nil(node); }

Node<T>* min_node(Node<T>* l, Node<T>* r) {
    if (is_nil(l)) {
        return r;
    }
    if (is_nil(r)) {
        return l;
    }
    return l->data < r->data ? l : r;
}

Node<T>* max_node(Node<T>* l, Node<T>* r) {
    if (is_nil(l)) {
        return r;
    }
    if (is_nil(r)) {
        return l;
    }
    return l->data < r->data ? r : l;
}

Node* max_element(Node* node) {
    if (is_real(node)) {
        node = max_node(node, max_element(node->left));
        node = max_node(node, max_element(node->right));
    }
    return node;
}

Node* min_element(Node* node) {
    if (is_real(node)) {
        node = min_node(node, min_element(node->left));
        node = min_node(node, min_element(node->right));
    }
    return node;
}

bool is_bst(Node* node) {
    if (node->is_nil()) {
        return true;
    }

    auto m = node;
    m = max_node(m, max_element(node->left));
    m = min_node(m, min_element(node->right));
    return m == node && is_bst(node->left) && is_bst(node.right);
}

Node* min_node(Node* node) {
    assert (is_bst(node));

    if (node.is_nil()) {
        return node;
    }

    while (node->left->is_real()) {
        node = node->left;
    }

    return node;
}

Node* max_node(Node* node) {
    assert (is_bst(node));

    if (is_nil(node)) {
        return node;
    }

    while (node->right->is_real()) {
        node = node->right;
    }

    return node;
}


Node* find(Node* node, const T& x) {
    assert (is_bst(node));

    while (is_real(node)) {
        if (node->data < x)
            node = node->right;
        else if (x < node->data)
            node = node->left;
        else
            break;
    }
    return node;
}


Node* insert_bst(Node*& node, Node* what) {
    assert (is_bst(node) &&  is_real(what));

    if (is_nil(node)) {
        // what.parent = node ???
        node = what;
        return node;
    }

    if (what->data < node->data) {
        return insert(node->left, what);
    } else if (node->data < what->data) {
        return insert(node->right, what);
    }
    return node;
}

size_t black_height(Node* node) {
    if (is_nil(node))
        return 0;

    size_t h = is_black(node) ? 1 :0;
    return h + std::max(black_height(node->left), black_height(node->right));
}

bool is_rbtree(Node* node) {
    if (is_nil(node))
        return true;
    
    if (!is_bst(node))
        return false;

    if (is_red(node)) {
        if (!(node->left->is_black() && node.right.is_black())) {
            return false;
        }
    }
    return black_height(node->left) == black_height(node->right);
}


bool is_root(Node* node) {
    return is_nil(node.parent);
}


void fix_insert_rb_tree(Node* node) {
    assert(is_real(node));

    if (is_root(node))
        return;

    auto dad = node.parent;
    if (is_black(dad))
        return;

    if (is_root(dad)) {
        dad->set_black();
    }

    auto grandpa = dad.parent;
    auto uncle = get_uncle(dad);

    if (is_red(uncle)) {
        grandpa.flip();
        dad.flip();
        uncle.flip();
        fix_insert_rb_tree(grandpa);
    }

    if (dad == grandpa.right) {
        auto y = rotate_left(grandpa);
        node->set_black();
        fix_insert_rb_tree(y);
    } else {
        auto y = rotate_right(grandpa);
        node->set_black();
        fix_insert_rb_tree(y);
    }
}

void insert_rbtree(Node*& node, Node* what) {
    assert (is_rbtree(node), && is_real(what));
    auto pos = insert_bst(node, what);
    fix_insert_rb_tree(pos);
}


template <class TKey, class TValue>
class map {
public:
    typedef size_t size_type;
    typedef TKey key_type;
    typedef std::pair<const TKey, TValue> value_type;
    typedef value_type& reference;

    typedef map<TKey, TValue> self_type;

public:
    map() : root(nullptr) {}

    map(const self_type& rhs)
    : root(nullptr) {
        this->assign(rhs.begin(), rhs.end());
    }

    ~map() {
        auto it = begin();
        while (!empty()) {
            it = this->erase(it);
        }
    }


    self_type& operator=(const self_type& rhs) {
        if (this != &rhs) {
            this->swap(self_type(ths));
        }
        return *this;
    }

    vois swap(self_type& other) {
        std::swap(root, other.root);
    }

    template <class TIter>
    void assign(TIter b, TIter e) {
        self_type tmp;
        for (auto it = b; it != e; ++it) {
            tmp.insert(*it);
        }
        swap(tmp);
    }

public:

    iterator begin() {
        return min_node(root);
    }

    iterator end() {
        return nullptr;
    }

    iterator insert(reference x) {
        auto what = new Node<value_type>(x);
        auto where = insert_rbtree(root, what);
        return iterator(where);
    }

    iterator find(const key_type& key) {
        return find(root, key);
    }

    reference operator[](const key_type& key) {
        auto pos = this->find(key);
        if (pos == end()) {
            pos = insert(key, TValue());
        }
        return *pos;
    }

private:
    Node<value_type>* root;
}


