import networkx as nx
import matplotlib.pyplot as plt
import binaryTreesAlgorithms as BTA

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
		for node in BTA.dfs_in_order(self):
			if node.parent:
				g.add_edge(node.data, node.parent.data)
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
