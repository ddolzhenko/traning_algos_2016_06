import networkx as nx
import matplotlib.pyplot as plt

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
		for node in dfs_in_order(self):
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

def dfs_pre_order(tree):
	if tree:
		yield tree
		dfs_pre_order(tree.left)
		dfs_pre_order(tree.right)

def dfs_pre_order_imperative(tree):
	if tree:
		queue = Queue()
		queue.push(tree)
		while not queue.empty():
			node = queue.pop_back()
			while node:
				yield node
				if node.right:
					queue.push(node.right)
				if node.left:
					node = node.left
				elif node.right:
					if queue._data[-1] == node.right:
						queue.pop_back()
					node = node.right
				else:
					node = None
				
def dfs_in_order(tree):
	if tree:
		yield from dfs_in_order(tree.left)
		yield tree
		yield from dfs_in_order(tree.right)

def dfs_post_order(tree):
	if tree:
		yield from dfs_post_order(tree.left)
		yield from dfs_post_order(tree.right)
		yield tree

def dfs_nodes(tree):
	if tree:
		yield from dfs_nodes(tree.left)
		yield tree
		yield from dfs_nodes(tree.right)

def remove_if(seq, pred):
	for x in seq:
		if not pred(x):
			yield x

def height(tree):
	if not tree:
		return 0
	return 1 + max(height(tree.left), height(tree.right))

def is_bst(tree):
	if not tree:
		return True



class Queue:
	def __init__(self):
		self._data = []

	def push(self, x):
		self._data.append(x)

	def pop(self):
		return self._data.pop(0)

	def pop_back(self):
		return self._data.pop()

	def empty(self):
		return len(self._data) == 0

	def __str__(self):
		return str(self._data)

def bfs(tree):
	queue = Queue()
	queue.push(tree)
	
	while not queue.empty():
		node = queue.pop()

		if node:
			yield node
			queue.push(node.left)
			queue.push(node.right)

def create_tree():
	t = Tree(13,
			Tree(8,
				Tree(1,
					right = Tree(6)),
				Tree(11,
					left = Tree(10))),
			Tree(17,
				Tree(15),
				Tree(25,
					Tree(19),
					Tree(27))))
	return t


def main():
	
	t = create_tree()

	dfs_pre_order(t)
	
	print("****************************")
	#dfs_in_order(t, print)
	#print("****************************")
	#dfs_post_order(t, print)
	#print("****************************")
	#print("****************************")
	#for node in dfs_nodes(t):
	#	print(node)

	#print("****************************")
	#print("---".join(map(str, dfs_nodes(t))))

	#print("****************************")
	#it = dfs_nodes(t)
	#for x in range(4):
	#	print (next(it))
	#
	#print("****************************")
	#for x in remove_if(dfs_nodes(t), lambda x: x.data%3 != 0):
	#	print (x)

	#print("****************************")
	#print(", ".join(map(str, remove_if(dfs_nodes(t), lambda x: x.data%3 != 0))))

	#print("****************************")
	#for x in bfs(t): 
	#	print(x)
	#print("****************************")
	#print(list(map(str, bfs(t))))
	#print("****************************")
	for x in dfs_pre_order_imperative(t):
		print(x)
	t.draw()
	

if __name__ == '__main__':
	main()

