import trees

from trees import Tree

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
    if is_nil(tree):
        return True
    return  (is_nil(tree.left) or   max_node(tree.left) < tree)  and \
            (is_nil(tree.right) or  tree < min_node(tree.right)) and \
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
		if node.parent.left == node:
			node.parent.left = None
		else:
			node.parent.right = None

	elif is_nil(node.left):
		if node.parent.left == node:
			node.parent.left = node.right
		else:
			node.parent.right = node.right

	elif is_nil(node.right):
		if node.parent.left == node:
			node.parent.left = node.left
		else:
			node.parent.right = node.left

	else:
		leaf = max_node(node.left)
		node.data, leaf.data = leaf.data, node.data
		remove(leaf)

	assert is_bst(node)

def create_tree_3():
	t = Tree

def main():
    t = trees.create_tree_2()
    

    insert(t, -1)
    insert(t, 12)
    insert(t, 26)
    insert(t, 18)
    #insert(t, 30)

    #remove(find(t, 25))

    print(list(map(str, trees.dfs_nodes_inorder(t))))
    print(list(map(str, iterate_forward(t))))
    print(list(reversed(list(map(str, iterate_backward(t))))))

    print(find(t, 10))

    print(is_bst(t))

    t.draw()

if __name__ == '__main__':
    main()