
        
class Tree:
    #constructor: explicit this -> self
    def __init__(self, data, left=None, right=None):
        # assert isinstance(left, Tree)
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)


def traverse_1(tree, visitor): #UP->DOWN && LEFT->RIGHT === PRE_ORDER
    if tree == None:
        return;
    visitor(tree.data)
    traverse_1(tree.left, visitor)
    traverse_1(tree.right, visitor)

def traverse_2(tree, visitor): #LEFT->RIGHT && DOWN->UP === IN_ORDER
    if tree == None:
        return;
    traverse_2(tree.left, visitor)
    visitor(tree.data)
    traverse_2(tree.right, visitor)

def traverse_3(tree, visitor): #ALL CHILDREN FIRST === POST_ORDER
    if tree == None:
        return;
    traverse_3(tree.left, visitor)
    traverse_3(tree.right, visitor)
    visitor(tree.data)

def create_tree():
    t = Tree(8,
            Tree(3,
                Tree(1),
                Tree(6,
                    Tree(4),
                    Tree(7)
                )
            ),
            Tree(10,
                right=Tree(14,
                            Tree(13)
                    )
            )
        )
    return t

def dfs_nodes(tree):
    #PRE_ORDER
    if tree:
        yield tree
        yield from dfs_nodes(tree.left)
            #for x in dfs_nodes(tree.left)
            #yield x
        yield from dfs_nodes(tree.right)
    pass

# example LIST ITERATOR
#def list_iter(node):
#    if node:
#        yield node.next

def remove_if(sequence, predicate):
    for x in sequence:
        if not predicate(x):
            yield x

def get_height(tree):
    pass

def bfs(tree, visitor): #UP->DOWN && LEFT->RIGHT // breadth first search
    if not tree :
        return

    next_Level = []
    for x in tree :
        visitor(x)
        if x.left :
            next_Level.append(x.left)
        if x.right :
            next_Level.append(x.right)

    bfs(next_Level, visitor)

class Queue:
    def __init__(self):
        self._data = []

    def push(self, x):
        self._data.append(x)

    def pop(self):
        return self._data.pop(0)

    def empty(self):
        return len(self._data) == 0


def bfs_queue(tree):
    queue = Queue()
    queue.push(tree)

    while not queue.empty():
        node = queue.pop()

        if node:
            yield node
            queue.push(node.left)
            queue.push(node.right)

def main():
    t = create_tree()

    print(Tree.__name__)
    #print(dir(Tree)) - content of class

    Tree.foo = lambda self, x: print(self.data + x)
    t.foo(12)
    del Tree.foo # delete method from class
    #t.foo(10) - ERROR!!!

    #traverse_1(t, print)
    #traverse_2(t, print)
    #traverse_3(t, print)

    for node in dfs_nodes(t):
        print(node)

    print(", ".join(map(str, dfs_nodes(t))))

    it = dfs_nodes(t) #FUCK MY BRAIN - it is ITERATOR!!!
    for x in range(4):
        print(next(it))

    #print only numbers that could be divided by 3
    print(", ".join(map(str, remove_if(range(1,15), lambda x: x%3 != 0))))
    print(", ".join(map(str, remove_if(dfs_nodes(t), lambda x: x.data%3 != 0))))

    #list [1,2,3,4,5,6,7,8,9,10]
    print(type([1,2,3]))
    print(", ".join(map(str, remove_if([1,2,3,4,5,6,7,8,9,10], lambda x: x%3 != 0))))

    sss = ", ".join(map(lambda x: str(x*3), [1,"ded",[123],3]))
    print(sss.split(','))

    #slovar "map"
    m = {
        "k1" : 123,
        "k2" : 321
    }
    print(type(m))
    print(m["k1"])
    m["k3"] = 345
    print(m["k3"])

    bfs([t], print)

    print(list(map(str, bfs_queue(t))))

    squares = [x.data*x.data for x in bfs_queue(t)];
    print(squares)

    squares = [x for x in squares if x > 100]
    print(squares)

    squares = {str(x) : x for x in squares if x > 100}
    print(squares)




if __name__ == '__main__':
    main()
