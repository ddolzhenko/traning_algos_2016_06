
import trees
#import search

def is_bst(tree): #is Binary Search Tree
    if not tree:
        return True

    return  (not tree.left  or max_node(tree.left) < tree) and \
            (not tree.right or tree < min_node(tree.right)) and \
            is_bst(tree.left) and is_bst(tree.right)

# write is_bst without min_node and max_node

def min_node(tree):
    if not tree.left:
        return tree

    return min_node(tree.left)

def max_node(tree):
    while tree.right:
        tree = tree.right

    return tree

def is_nil(tree):
    return tree is None

def rotate_left(x):
    assert x
    assert x.right
    assert is_bst(x)

    y = x.right
    b = y.left

    if x.parent and x.parent.right == x:
        x.parent.right = y
    else:
        x.parent.left = y

    y.parent = x.parent
    y.left = x
    x.parent = y
    x.right = b
    if b:
        b.parent = x

    assert is_bst(y)

def rotate_right(y):
    assert y
    assert y.left
    assert is_bst(y)

    x = y.left
    b = x.right

    if y.parent and y.parent.right == y:
        y.parent.right = x
    else:
        y.parent.left = x
        
    x.parent = y.parent
    x.right = y
    y.parent = x
    y.left = b
    if b:
        b.parent = y

    assert is_bst(x)

def find(tree, x):
    if tree:
        if x < tree.data:
            return find(tree.left, x)
        if x > tree.data:
            return find(tree.right, x)

    return tree

def main():
    t = trees.create_tree_2()
    t.draw()
    node = find(t, 17)
    rotate_left(node)
    t.draw()
    node = find(t, 25)
    rotate_right(node)
    t.draw()
    

if __name__ == '__main__':
    main()

