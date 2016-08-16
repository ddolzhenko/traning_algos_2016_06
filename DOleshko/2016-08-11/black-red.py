import tree_srv
import trees
import networkx as nx
import matplotlib.pyplot as plt

#def is_nil(tree):
#    return tree == Tree.nil
#
#def is_bst(tree):
#    return tree_srv.is_bst(tree, lambda x: x.is_nil)

def dfs_nodes_inorder(tree):
    if not tree.is_nil:
        yield from dfs_nodes_inorder(tree.left)
        yield tree
        yield from dfs_nodes_inorder(tree.right)

class BaseTree:
    def __init__(self, nil=None):
        self.left   = nil
        self.right  = nil
        self.parent = nil
        self._is_black = True

    @property
    def is_black(self):
        return self._is_black

    @is_black.setter
    def is_black(self, value):
        self._is_black = value

    @property
    def is_red(self):
        return not self._is_black

    @property
    def is_valid(self):
        return is_rbtree(self)

    @property
    def dad(self):
        return self.parent

    @dad.setter
    def dad(self, value):
        self.parent = value

    @property
    def grandpa(self):
        if not self.dad.is_nil:
            return self.dad.parent
        else:
            return Tree.nil

    @property
    def uncle(self):
        if self.grandpa.is_nil:
            return Tree.nil

        if self.grandpa.left == self.dad:
            return self.grandpa.right
        else:
            return self.grandpa.left        
    
    @property
    def is_nil(self):
        return self == Tree.nil

    def __str__(self):
        return str(self.data)

    def __lt__(self, other):
        return True        




class Tree(BaseTree):

    nil = BaseTree() #common for all class objects

    def __init__(self, x):
        super().__init__(Tree.nil)
        self.data = x

    def __lt__(self, other):
        return self.data < other.data


    def to_graph(self):
        g = nx.Graph()
        for node in dfs_nodes_inorder(self):
            if not node.parent.is_nil:
                g.add_edge(node.data, node.parent.data)
                g.node[node.data]['color'] = 'grey' if node.is_black else 'red'
                g.node[node.parent.data]['color'] = 'grey' if node.parent.is_black else 'red'
                print(g.node)

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
        nx.draw_networkx(g, positions, node_size=1500, font_size=24, node_color=[g.node[node]['color'] for node in g])
        plt.show()    

    
def is_rbtree(tree):
    #assert tree_srv.is_bst(tree)

    def RB_conditions(tree):
        assert isinstance(tree, BaseTree)
    
        if tree.is_nil:
            return tree.is_black
    
        if tree.is_red:
            if tree.right.is_red or tree.left.is_red:
                return False

        return RB_conditions(tree.left) and RB_conditions(tree.right)

    def BlackRoute_condition(tree):
        if tree:
            left_ok,  leftBlackLen  = BlackRoute_condition(tree.left)
            right_ok, righBlacktLen = BlackRoute_condition(tree.right)

            ok = (left_ok and right_ok and leftBlackLen == righBlacktLen)
            return ok, leftBlackLen + (1 if tree.is_black else 0)

        return True, 0

    return RB_conditions(tree) and BlackRoute_condition(tree)[0]

def fix_rbtree(node):

    #case ROOT
    if node.dad.is_nil:
        return
    
    #case 0:
    if node.parent.is_black:
        return

    #else dad is red

    if node.grandpa.is_nil: #dad is ROOT
        pass

    #case 1:
    if uncle(node).is_red:
        parent(node).flip_color()
        uncle(node).flip_color()
        grandpa(node).flip_color()
        fix_rbtree(grandpa(node))
        return

    #case 2: uncleis black
    if dad == grandpa.right:
        bst.rotate_left(grandpa)
        node.flip_color()
        return
    else:
        bst.rotate_right
        node.flip_color()
        return



def rb_insert(root, x):
    assert root.is_valid


def main():
    #for x in globals():
        #print(x)

    t = Tree(5)
    t.is_black = True

    t.left = Tree(2)
    t.left.dad = t
    t.left.is_black = False

    t.right = Tree(10)
    t.right.dad = t
    t.right.is_black = False

    t.right.left = Tree(8)
    t.right.left.dad = t.right
    t.right.left.is_black = True

    t.draw()
    print(is_rbtree(t))

if __name__ == '__main__':
    main()

