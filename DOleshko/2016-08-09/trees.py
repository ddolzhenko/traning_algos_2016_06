import networkx as nx
import matplotlib as plt

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

    def to_graph(self):
        g = nx.Graph()
        for node in dfs_nodes_inorder(self):
            if node.left:
                g.add_edge(node.data, node.left.data)
            if node.right:
                g.add_edge(node.data, node.right.data)
        return g

    def get_positions(node, positions, x, y):
        if node:
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
                    Tree(27))))
                
    return t