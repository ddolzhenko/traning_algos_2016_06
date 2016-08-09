class Tree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
        self.parent = None
        if self.left:
            self.left.parent = self
        if self.right:
            self.right.parent = self

    def __lt__(self, other):
        return self.data < other.data

    def __str__(self):
        return str(self.data)


def dfs_pre_order(tree, visit):
    if tree:
        visit(tree)
        dfs_pre_order(tree.left, visit)
        dfs_pre_order(tree.right, visit)

def dfs_in_order(tree, visit):
    if tree:
        dfs_in_order(tree.left, visit)
        visit(tree)
        dfs_in_order(tree.right, visit)

def dfs_post_order(tree, visit):
    if tree:
        dfs_post_order(tree.left, visit)
        dfs_post_order(tree.right, visit)
        visit(tree)

def dfs_nodes_inorder(tree):
    if tree:
        yield from dfs_nodes_inorder(tree.left)
        yield tree
        yield from dfs_nodes_inorder(tree.right)

    
def height(tree):
    if not tree:
        return 0
    return max(height(tree.left), height(tree.right)) + 1

class Queue:
    def __init__(self):
        self._data = []

    def push(self, x):
        self._data.append(x)

    def pop(self):
        return self._data.pop(0)

    def empty(self):
        return len(self._data) == 0


def bfs(tree): # breadth-first search
    queue = Queue()
    queue.push(tree)
    while not queue.empty():
        node = queue.pop()
        if node:
            yield node
            queue.push(node.left)
            queue.push(node.right)    
    

def create_tree():
    t = Tree(8,
            Tree(3,
                Tree(1),
                Tree(6,
                    Tree(4),
                    Tree(7))),
            Tree(10,
                right=Tree(14,
                        Tree(13))))
    return t

def create_tree_2():
    t = Tree(13,
            Tree(8,
                Tree(1,
                    right=Tree(6)),
                Tree(11,
                    Tree(10))),
            Tree(17,
                Tree(15),
                Tree(25,
                    Tree(19),
                    Tree(27, 
                        Tree(100,
                            Tree(200))))))
                
    return t

def list_iter(node):
    if node:
        yield node.next

def remove_if(seq, pred):
    for x in seq:
        if not pred(x):
            yield x

def yield_experiments():
    t = create_tree()
    print("-----".join(map(str, dfs_nodes_inorder(t))))

    it = dfs_nodes_inorder(t)
    for x in range(4):
        print(next(it))

    print(", ".join(
        map(str, 
            remove_if(dfs_nodes_inorder(t), 
                lambda x: x.data%3 != 0))))


    print(", ".join(
        map(str, 
            remove_if([1,2,3,4,5,6,7, 99], 
                    lambda x: x%3 != 0))))
        
    m = {
        "k1" : 123,
        "k2" : 321
    }

    print(m["k1"])
    m['k3'] = 43

################################bst#########################################3

def is_nill(tree):
    return tree is None

def min_node(tree):
    assert tree is not None
    while(tree.left):
        tree = tree.left
    return tree

def max_node(tree):
    assert tree is not None
    while(tree.right):
        tree = tree.right
    return tree

def is_bst(tree):
    if is_nill(tree):
        return True
    
    return (is_nill(tree.left) or max_node(tree.left) < tree) and \
           (is_nill(tree.left) or tree < min_node(tree.left)) and \
            is_bst(tree.left and is_bst(tree.right))

def next_node(tree):
    assert not is_nill(tree)
    if not is_nill(tree.right):
        return min_node(tree.right)

    while not is_nill(tree) and tree.parent.right == tree:
        tree = tree.parent

    return tree.parent

def prev_node(tree):
    assert not is_nill(tree)
    if not is_nill(tree.left):
        return min_node(tree.left)

    while not is_nill(tree) and tree.parent.left == tree:
        tree = tree.parent

    return tree.parent

def forward_iterator(tree):
    it = min_node
    while not is_nill(it):
        yield it
        it = next_node(it)

def backward_iterator(tree):
    it = max_node
    while not is_nill(it):
        yield it
        it = prev_node(it)

def find(tree, x):
    if not is_nill(tree):
        if x < tree.data:
            return find(tree.left, x)
        if tree.data < x:
            return find(tree.right, x)

    return tree

def insert(tree, x):    #HW: delete func
    assert(is_bst(tree))
    if is_nill(tree):
        return Tree(x)

    if x < tree.data:
        if(is_nill(tree.left)):
            tree.left = Tree(x)
            tree.left.parent = tree
            return tree.left
        else:
            return insert(tree.left, x)

    if tree.data < x:
        if(is_nill(tree.left)):
            tree.right = Tree(x)
            tree.right.parent = tree
            return tree.right
        else:
            return insert(tree.right, x)
    
    return tree

def remove(tree, x):
    assert(is_bst(tree))

    node = find(tree, x)

    if not is_nill(node):
        return

    if is_nill(node.left) and is_nill(node.right):
        if node.parent.left == node:
            node.parent.left = None
        else:
            node.parent.right = None
    elif node.parent.left == node:
        node.parent = node.left
    else:
        node.parent.right = node.left
            
    assert(is_bst(tree))

    

#########################################################################

def main():
    t = create_tree()
    t2 = create_tree_2()
    print(list(map(str, dfs_nodes_inorder(t))))
    print(list(map(str, dfs_nodes_inorder(t2))))
    if(is_bst(t2)):
        print(list(map(str, forward_iterator(t2))))

    
    print(height(t))
    print(height(t2))
    print(find(t, 8))

    insert(t, 9)
    insert(t, 12)
    print(list(map(str, dfs_nodes_inorder(t))))

    #print(list(map(str, bfs(t))))

    #squares = [x.data*x.data for x in bfs(t)]

    #squares = { str(x) : x for x in squares if x > 100}
    #print(squares)

if __name__ == '__main__':
    main()