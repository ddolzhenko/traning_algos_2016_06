#include "rb_tree.hpp"

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
};
