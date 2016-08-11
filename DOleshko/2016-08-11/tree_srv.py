
#def is_bst(tree): #is Binary Search Tree
#    if not tree:
#        return True
#
#    return  (not tree.left  or max_node(tree.left) < tree) and \
#            (not tree.right or tree < min_node(tree.right)) and \
#            is_bst(tree.left) and is_bst(tree.right)

# write is_bst without min_node and max_node

def is_nil(tree):
    return tree is None

def is_bst(tree, is_nil=is_nil): #is Binary Search Tree
    if is_nil(tree):
        return True
        
    return  (is_nil(tree.left)  or  max_node(tree.left) < tree)  and \
            (is_nil(tree.right) or  tree < min_node(tree.right)) and \
            is_bst(tree.left) and is_bst(tree.right)

def min_node(tree):
    if not tree.left:
        return tree

    return min_node(tree.left)

def max_node(tree):
    while tree.right:
        tree = tree.right

    return tree

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
        if x > tree.data:
            return find(tree.right, x)

    return tree

def insert(tree, x):
    if is_nil(tree):
        return trees.Tree(x)

    if x < tree.data:
        if is_nil(tree.left):
            tree.left = trees.Tree(x)
            tree.left.parent = tree
            return tree.left
        else:
            return insert(tree.left, x)
    if x > tree.data:
        if is_nil(tree.right):
            tree.right = trees.Tree(x)
            tree.right.parent = tree
            return tree.right
        else:
            return insert(tree.right, x)

    return tree