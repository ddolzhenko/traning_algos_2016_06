import tree
from tree import Tree
import queue
from queue import Queue

def dfs_pre_order(tree):
	if tree:
		yield tree
		dfs_pre_order(tree.left)
		dfs_pre_order(tree.right)

def dfs_pre_order_imperative(tree):
	if tree:
		queue = Queue()
		queue.push(tree)
		while not queue.empty():
			node = queue.pop_back()
			while node:
				yield node
				if node.right:
					queue.push(node.right)
				if node.left:
					node = node.left
				elif node.right:
					if queue._data[-1] == node.right:
						queue.pop_back()
					node = node.right
				else:
					node = None
				
def dfs_in_order(tree):
	if tree:
		yield from dfs_in_order(tree.left)
		yield tree
		yield from dfs_in_order(tree.right)

def dfs_post_order(tree):
	if tree:
		yield from dfs_post_order(tree.left)
		yield from dfs_post_order(tree.right)
		yield tree

def dfs_nodes(tree):
	if tree:
		yield from dfs_nodes(tree.left)
		yield tree
		yield from dfs_nodes(tree.right)

def remove_if(seq, pred):
	for x in seq:
		if not pred(x):
			yield x

def height(tree):
	if not tree:
		return 0
	return 1 + max(height(tree.left), height(tree.right))

def is_bst(tree):
	if not tree:
		return True

def is_nil(tree):
	return tree is None

def min_node(tree):
	assert not is_nil(tree)
	while tree.left:
		tree = tree.left
	return tree

def max_node(tree):
	assert not is_nil(tree)
	while tree.right:
		tree = tree.right
	return tree

def is_bst(tree):
	if not tree:
		return True
	return (is_nil(tree.left) or max_node(tree.left) < tree) and\
		   (is_nil(tree.right) or tree < min_node(tree.right)) and\
		   is_bst(tree.left) and is_bst(tree.right)

def next_node(tree):
	assert not is_nil(tree) 
	if not is_nil(tree.right):
		return min_node(tree.right)
	while not is_nil(tree.parent) and tree.parent.right == tree:
		tree = tree.parent
	return tree.parent

def prev_node(tree):
	assert not is_nil(tree) 
	if not is_nil(tree.left):
		return max_node(tree.left)
	while not is_nil(tree.parent) and tree.parent.left == tree:
		tree = tree.parent
	return tree.parent

def iterate_forward(tree):
	it = min_node(tree)
	while not is_nil(it):
		yield it
		it = next_node(it)

def iterate_backward(tree):
	it = max_node(tree)
	while not is_nil(it):
		yield it
		it = prev_node(it)

def find(tree, x):
	if not is_nil(tree):
		if x < tree.data:
			return find(tree.left, x)
		if tree.data < x:
			return find(tree.right, x)
	return tree

def insert(tree, x):
	if is_nil(tree):
		return Tree(x)
	
	if x < tree.data:
		if is_nil(tree.left):
			tree.left = Tree(x)
			tree.left.parent = tree
			return tree.left
		else:
			return insert(tree.left, x)
	
	if tree.data < x:
		if is_nil(tree.right):
			tree.right = Tree(x)
			tree.right.parent = tree
			return tree.right
		else:
			return insert(tree.right, x)
	assert is_bst(tree)
	return tree

def remove(node):
	assert is_bst(node) and not is_nil(node)
	assert not is_nil(node.parent)

	def assign_to_parent(what):
		if node.parent.left == node:
			node.parent.left = what
		else:
			node.parent.right = what

	if is_nil(node.left) and is_nil(node.right):
		assign_to_parent(None)

	elif is_nil(node.left):
		assign_to_parent(node.right)
		node.right.parent = node.parent
	elif is_nil(node.right):
		assign_to_parent(node.left)
		node.left.parent = node.parent
	else:
		leaf = max_node(node.left)
		node.data, leaf.data = leaf.data, node.data
		remove(leaf)
	assert is_bst(node)

