import bst
import networkx as nx
import matplotlib.pyplot as plt

# def is_bst(tree):
#     return bst.is_bst(tree, lambda x: x.is_nil)

from bst import max_node, min_node

def is_bst(tree):
    if tree.is_nil:
        return True

    print(type(tree))
    print(type(tree.left))
    print(type(tree.right))
    print(max_node(tree.left) < tree)

    mn = min_node(tree.right)
    print(mn)
    print(type(mn))
    return  (max_node(tree.left) < tree < min_node(tree.right))  and \
            is_bst(tree.left) and is_bst(tree.right)


def dfs_nodes_inorder(tree):
    if not tree.is_nil:
        yield from dfs_nodes_inorder(tree.left)
        yield tree
        yield from dfs_nodes_inorder(tree.right)



class BaseTree:
    def __init__(self, nil=None):
        self.parent = nil
        self.left =  nil
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

    def __str__(self):
        return 'nil'


class Tree(BaseTree):
    nil = BaseTree()

    def __init__(self, x):
        super().__init__(Tree.nil)
        self.data = x
        
    def __lt__(self, other):
        return self.data < other.data

    def __str__(self):
        return str(self.data)

    @property
    def is_valid(self):
        return is_rbtree(self)
    
    def to_graph(self):
        g = nx.Graph()
        for node in dfs_nodes_inorder(self):
            if not node.parent.is_nil:
                g.add_edge(node.data, node.parent.data)
        return g

    def get_positions(node, positions, x, y):
        if not node.is_nil:
            node_size = 0.5
            my_x = (x[1] + x[0]) / 2
            my_y = y[0] + (node_size / 2)
            positions[node.data] = (my_x, -my_y)
            Tree.get_positions(node.left, positions, (x[0], my_x), (my_y, y[1]))
            Tree.get_positions(node.right, positions, (my_x, x[1]), (my_y, y[1]))

    def draw(self):
        positions = {}
        Tree.get_positions(self, positions, x=(0, 10), y=(0, 10))
        g = self.to_graph()

        plt.axis('on')
        nx.draw_networkx(g, positions, node_size=1500, font_size=24, node_color='g')
        plt.show()

def is_rbtree(tree):
    assert is_bst(tree)

    def cond_4_6(tree):
        assert isinstance(tree, BaseTree)

        if tree.is_nil:
            return tree.is_black

        if tree.is_red:
            if tree.right.is_red or tree.left.is_red:
                return False

        return cond_4_6(tree.left) and cond_4_6(tree.right)

    def black_route(tree):
        if tree:
            left_ok, llen = black_route(tree.left)
            right_ok, rlen = black_route(tree.right)
            
            ok = (left_ok and right_ok and llen==rlen)
            return ok, llen + (1 if tree.is_black else 0)

        return True, 0


    return cond_4_6(tree) and black_route(tree)[0]


def insert(root, x):
    assert root.is_valid

    node = bst.insert(root, x)


    assert root.is_valid


def main():

    t = Tree(13)
    t.right = Tree(17)
    t.right.parent = t
    t.right._is_black = False
    
    print(t.data, t.right.data, t.left < t < t.right)

    # exit()


    insert(t, 10)

    t.draw()

if __name__ == '__main__':
    main()


