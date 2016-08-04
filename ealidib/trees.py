class Tree:
	def __init__(self, data, left=None, right=None):
		self.data = data
		self.left = left
		self.right = right

	def __str__(self):
		return str(self.data)

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
		
def dfs_nodes(tree):
	if tree:		
		yield from dfs_nodes(tree.left)
		yield tree
		yield from dfs_nodes(tree.right)

def remove_if(seq, pred):
	for x in seq:
		if not pred(x):
			yield x

####################### DZ
def height(tree):
	pass

class Queue:
	def __init__(self):
		self._data = []

	def push(self, x):
		self._data.append(x)

	def pop(self):
		return self._data.pop(0)

	def empty(self):
		return len(self._data) == 0
def bfs(tree): # breadth-first search
	queue = Queue()

	queue.push(tree)
	while not queue.empty():
		node = queue.pop()

		if node:
			yield node
			queue.push(node.left)
			queue.push(node.right)

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

def main():
	t = create_tree()
	#dfs_in_order(t, print)

	# for node in dfs_nodes(t):
	# 	print(node)

	print("----".join(map(str, dfs_nodes(t))))
	it = dfs_nodes(t)
	for x in range(4):
		print(next(it))

	print(", ".join(
		map(str,
		 remove_if(dfs_nodes(t),
		  lambda x: x.data%3 != 0))))

	print("----".join(map(str, bfs(t))))


if __name__ == '__main__':
	main()