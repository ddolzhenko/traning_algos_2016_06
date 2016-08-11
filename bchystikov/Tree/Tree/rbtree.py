import bst

class BaseTree:
    def __init__(self, nil = None):
        self.parent = nil
        self.left   = nil
        self.right  = nil
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

class Tree(BaseTree):

    nil = BaseTree(None)    #analog static, belong to class, not objects

    def is_bst(tree):
        #def is_nil(x):
        #    return x.is_nil
        return bst.is_nil(tree, lambda x: x.is_nil)

    def __init__(self, x):
        self.data = x
        super().__init__(Tree.nil)


def is_rbtree(tree):
    assert is_bst(tree)
    
    def cond_4_6(tree):
        assert isinstance(tree, Tree)

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
  
def main():
    pass

if __name__ == '__main__':
    main()