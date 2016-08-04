
class Tree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
    
    def __str__(self):
        return str(self.data)

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

#depth first search
def dfs_preorder(tree, visit):    #preorder
    if tree:
        visit(tree)
        dfs_preorder(tree.left, visit)
        dfs_preorder(tree.right, visit)

def dfs_inorder(tree, visit):    #inorder
    if tree:
        dfs_inorder(tree.left, visit)
        visit(tree)
        dfs_inorder(tree.right, visit)

def dfs_postorder(tree, visit):    #postorder
    if tree:
        dfs_postorder(tree.left, visit)
        dfs_postorder(tree.right, visit)
        visit(tree)

def dfs_nodes(tree):    
    if tree:
        yield from dfs_nodes(tree.left)
        yield tree
        yield from dfs_nodes(tree.right)
        #for x in dfs_nodes(tree.left):
        #    yield x

def remove_if(seq, pred):
    for x in seq:
        if not pred(x):
            yield x

def list_iter(node):
    if node:
        yield node.next

def height(tree):   #HW
    pass



def bfs(tree):  #breadth-first search
    que = list()

    que.push(tree)
    while not que.empty():
        node = que.pop()
        if node:
            yield node
            que.push(node.left)
            que.push(node.right)


def main():
    t = create_tree()
    #dfs_preorder(t, print)

    #for node in dfs_nodes(t):
    #    print(node)
    
    print(", ".join(map(str, dfs_nodes(t))))
    it = dfs_nodes(t)
    
    [x.data*x.data for x in dfs_nodes(t)]

    #for x in range(4):
    #    print(next(it))

    #for x in remove_if(range(1, 100), lambda x: x%3 != 0):
    #    print(x)

    #print(", ".join(map(str, remove_if( range(1, 100), lambda x: x%3 != 0))))

    #print(", ".join(
    #    map(str, 
    #        remove_if( dfs_nodes(t), 
    #            lambda x: x.data%3 != 0))))



if __name__ == '__main__':
    main()

#dir - print of attributes