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


def is_bst(tree, is_nil=is_nil):
    if is_nil(tree):
        return True

    print(is_nil(tree))
    print(is_nil(tree.left))
    print(is_nil(tree.right))
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
    assert is_bst(tree)

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
        print(leaf)
        node.data, leaf.data = leaf.data, node.data
        remove(leaf)
   
    assert is_bst(node)

def rotate_left(x):
    assert is_bst(x)
    assert not is_nil(x)
    assert not is_nil(x.right)

    y = x.right
    a = x.left
    b = y.left
    c = y.right

    if not is_nil(x.parent):
        if x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y

    y.parent = x.parent
    y.left = x
    
    x.parent = y
    x.right = b

    if not is_nil(b):
        b.parent = x

    assert is_bst(y)
    return y

def rotate_right(y):
    assert is_bst(y)
    assert not is_nil(y)
    assert not is_nil(y.left)

    x = y.left
    a = x.left
    b = x.right
    c = y.right

    if not is_nil(y.parent):
        if y == y.parent.left:
            y.parent.left = x
        else:
            y.parent.right = x

    x.parent = y.parent
    x.right = y

    y.parent = x
    y.left = b
    
    if not is_nil(b):
        b.parent = y

    assert is_bst(x)
    return x


def create_tree_3():
    t = Tree(13)
    for x in range(1, 10):
        insert(t, x)
    return t

def create_tree_4():
    t = Tree(13)
    import random
    arr = list(range(1, 26))
    random.shuffle(arr)
    for x in arr:
        insert(t, x)
    return t


def main():
    t = trees.create_tree_2()
    

    insert(t, -1)
    insert(t, 12)
    insert(t, 28)
    insert(t, 18)
    insert(t, 26)
    

    remove(find(t, 25))

    print(list(map(str, trees.dfs_nodes_inorder(t))))
    print(list(map(str, iterate_forward(t))))
    print(list(reversed(list(map(str, iterate_backward(t))))))

    print(find(t, 10))

    print(is_bst(t))
    
    t.draw()
    rotate_left(find(t, 17))
    t.draw()
    rotate_right(find(t, 19))
    t.draw()
    # create_tree_3().draw()
    # create_tree_4().draw()

if __name__ == '__main__':
    main()