import bst

class BaseTree():
    def __init__(self, nil=None):
        self.parent = nil
        self.left = nil
        self.right = nil
        self._is_black = True

    @property
    def is_black(self):
        return self._is_black

    @property
    def is_red(self):
        return not self._is_black

    @property
    def is_nil(self):
        return self == Tree.nil

    def __lt__(self, other):
        return True


class Tree(BaseTree):

    nil = BaseTree(None)    #analog static, belong to class, not objects

    def __lt__(self, other):
        return self.data < other.data

    @property
    def is_valid():
        return is_rbtree(self)

    def is_bst(tree):
        #def is_nil(x):
        #    return x.is_nil
        return bst.is_nil(tree, lambda x: x.is_nil)

    def __init__(self, x):
        super().__init__(Tree.nil)
        self.data = x


def is_rbtree(tree):
    assert bst.is_bst(tree)
    
    def cond_4_6(tree):
        assert isinstance(tree, BaseTree)

        if tree.is_nil:
            return tree.is_black

        if tree.is_red:
            if tree.right.is_red or tree.left.is_red: 
                return False

        return cond_4_6(tree.left) or cond_4_6(tree.right)
    
    def black_route(tree):
        if tree:
            left_ok, llen = black_route(tree.left)
            right_ok, rlen = black_route(tree.right)
            ok = (left_ok and right_ok and llen == rlen)
            return ok, (llen + (1 if tree.is_black else 0))    
        return True, 0

    return cond_4_6(tree) and black_route(tree)[0]
  
def is_root(node):
    pass

def fix_rbtree(node):
    #assert !node.is_black

    #case root
    if is_root(node):
        return

    dad = node.parent

    # case 0
    if dad.is_black:
        return

    grandpa = node.parent.parent

    if grandpa.is_nil:      #dad is root
        dad.flip_color

    if dad == grandpa.left:
        uncle = grandpa.red
    else:
        uncle = grandpa.left

    #parent is red
    #case 1
    if uncle(node).is_red:
        dad.flip_color()
        uncle.flip_color()
        grandparent.flip_color()
        fix_rbtree(grandparent)
        return
        
    #case 2(uncle is black)
    if dad == grandpa.right:
        y = bst.rotate_left(grandpa)
        node.flip_color()
        fix_rbtree(y)
        return
    else:
        y = bst.rotate_right(grandpa)
        node.flip_color()
        fix_rbtree(y)
        return



def insert(root, x):    #not finished
    assert root.is_valid
    
    node = bst.insert(root)
    node.is_black = False
    fix_rbtree(node)

    assert root.is_valid

def main():
    t = Tree(12)
    is_rbtree(t)
    #t.insert(Tree(10))

if __name__ == '__main__':
    main()