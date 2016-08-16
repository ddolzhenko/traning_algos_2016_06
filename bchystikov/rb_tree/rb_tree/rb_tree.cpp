#include "stdafx.h"
#include "cassert"

template <class T>
struct  Node
{
   Node(const T data)
      : left(nullptr)
      , right(nullptr)
      , parent(nullptr)
      , mIsBlack(false)
   {}

   Node * left;
   Node * right;
   Node * parent;
   bool mIsBlack;
   T data;
};

template <class T>
bool isBlack(Node<T> node)
{
   return node == nullptr || node.mIsBlack;
}

template <class T>
bool isRed(Node<T> node)
{
   return !isBlack(node);
}

template <class T>
bool isNil(Node<T> node)
{
   return node != node;
};

template <class T>
bool isReal(Node<T> node)
{
   return !isNil(this);
};

template <class T>
Node<T> minNode(const Node<T> l, const Node<T> r)
{
   if (isNil(l))
      return r;

   if (isNil(r))
      return l;

   return l->data < r->data ? l : r;
}

template <class T>
Node<T> maxNode(const Node<T> l, const Node<T> r)
{
   if (isNil(l))
      return r;

   if (isNil(r))
      return l;

   return l->data > r->data ? l : r;
}


template <class T>
Node<T> * max_elem(Node<T> * node)
{
   if (isNil(node))
      return node;

   node = max_node(node, max_elem(node->left));
   node = max_node(node, max_elem(node->right));
   return node;
}

template <class T>
bool isBST(Node<T> * node)
{
   if (node->isNil())
      return true;

   auto m = node;
   m = max_node(max_elem(node->left));
   m = min_node(max_elem(node->right));
   return (m == node) && isBST(node->left) && (isBST(node.right))
}

template <class T>
bool min_node(Node<T> * node)
{
   assert(isBST(node));

   if (isNil(node))
      return node;

   while (!isNil(node->left))
   {
      node = node->right;
   }
   return node;
}

template <class T>
Node<T> * find_rec(Node<T> * node, const T & x)
{
   if (isNil(node))
      return node;

   if (node->data < x)
      return find(node->right, x)
   else if (x < node->data->left, x)
      return find(node->left, x);

   return node;
}

template <class T>
Node<T> * find(Node<T> * node, const T & x)
{
   while (isReal(node))
   {
      if (node->data < x)
         node = (node->right, x)
      else if (x < node->data->left, x)
         node = (node->left, x);
      else
         break;
   }
   return node;
}

template <class T>
Node<T> * insert_bst(Node<T> *& node, Node<T> * what)
{
   assert(isBST(node) && isReal(what));

   if (isNil(node))
   {
      //what->parent = node ???
      node = what;   //!!!
      return what;
   }

   if (what->data < node->data)
   {
      return insert(node->left, what)
   }
   else if (node->data < what->data)
   {
      return insert(node->right, what)
   }
   return node;
}

template <class T>
size_t blackHeight(Node<T> * node)
{
   if (isNil(node))
      return 0;

   size_t h = isBlack(node) ? 1 : 0;
   return h + std::max(blackHeight(node->left), blackHeight(node->right))

}

template <class T>
bool isRBTree(Node<T> * node)
{
   if (!isBST(node))
      return false;

   if (isNil(node))
      return true;

   if (isRed(node))
   {
      if (!isBlack(node->left) && isBlack(node->right))
         return false;
   }
}

template <class T>
bool isRoot(Node<T> * node)
{
   return isNil(node.parent);
}


template <class T>
void fixInsertPos(Node<T> * node)
{
   if (isRoot(node))
      return;

   auto dad = node.parent;
   if (isBlack(dad))
      return;

   if (isRoot(dad))
   {
      dad->setBlack();
   }

   auto grandpa = dad.parent;
   auto uncle = get_uncle(dad);
   if (isRed(uncle))
   {
      grandpa.flip();
      dad.flip();
      uncle.flip();
      fixInsertPos(grandpa);
   }

   if (dad = grandpa.right)
   {
      auto y = rotateLeft(grandpa);
      node->setBlack();
      fixInsertPos(y);
   }
   else
   {
      auto y = rotateRight(grandpa);
      node->setBlack();
      fixInsertPos(y);
   }
}

template <class T>
void insertRBTree(Node<T> *& node, Node<T> * what)
{
   assert(isRBTree(node) && isReal(what));
   auto pos = insert_bst(node, what);
   assert(isReal(pos));
   fixInsertPos(pos);
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


int main()
{
   Node<int> node(0);


   return 0;
}

