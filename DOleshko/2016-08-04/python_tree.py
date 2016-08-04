
class ClassName(object):
    """docstring for ClassName"""
    def __init__(self, arg):
        super(ClassName, self).__init__()
        self.arg = arg
        
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


def main():
    t = create_tree()

    print(Tree.__name__)
    #print(dir(Tree)) - content of class

    Tree.foo = lambda self, x: print(self.data + x)
    t.foo(12)
    del Tree.foo
    #t.foo(10) - error

    #traverse_1(t, print)
    #traverse_2(t, print)
    traverse_3(t, print)

if __name__ == '__main__':
    main()
