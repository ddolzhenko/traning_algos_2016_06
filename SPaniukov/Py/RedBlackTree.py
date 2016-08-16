import binaryTreesAlgorithms as BTA


def is_nil(tree):
	return BTA.is_bst(tree, lambda x: x.is_nil)

class BaseTree():
	
	def __init__(self, nil = None):
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

class Tree(BaseTree):

	nil = BaseTree()

	def __init__(self, x):
		super.__init__(Tree.nil)
		self.data = x

	def __lt__(self, other):
		return self.data < other.data

	@property
	def is_valid(self):
		return is_rbtree(self)

	@property
	def flip_color(self):
			self._is_black = not self._is_black
	
def is_rbtree(tree):
	assert is_bst(tree)

	def cond_4_6(tree):
		assert isinstance(tree, Tree)

		if tree.is_nil:
			return tree.is_black

		if tree.is_red:
			if tree.left.is_red or tree.right.is_red:
				return False
		return cond_4_6(tree.left) and cond_4_6(tree.right)

	def black_route(tree):
		if tree:
			left_ok, llen = black_route(tree.left)
			right_ok, rlen = black_route(tree.right)
			ok = (left_ok and right_ok and llen == rlen)
			return ok, (llen + (1 if tree.is_black else 0))
		return True, 0

	return cond_4_6(tree) and black_route(tree)[0]
def function():
	pass

def uncle(node):
	if node.parent == node.parent.parent.left:
		return node.parent.parent.right
	elif node.parent == node.parent.parent.right:
		node.parent.parent.left

def parent(node):
	return node.parent

def grandparent(node):
	return node.parent.parent

def fix_rbtree(node):

	#case root
	if node.parent.is_nil:
		return
	#case 0
	if node.parent.is_black:
		return
	#else parent is red
	if grandparent(node).is_nil:#dad is root
		node.parent.flip_color()

	#case 1 uncle is red
	if uncle(node).is_red:
		parent(node).flip_color()
		uncle(node).flip_color()
		grandparent(node).flip_color()
		fix_rbtree(grandparent(node))
		return
	#case 2 uncle is black, dad is red
	if parent(node) == grandparent(node).right:
		BTA.rotate_left(grandparent(node))
	else:
		BTA.rotate_right(grandparent(node))
	node.flip_color()
	fix_rbtree(node)
	return

def insert(root):
	assert root.is_valid

	node = BTA.insert(root)
	node.is_black = False
	assert root.is_valid

def create_rbtree():
	pass

def main():
	t = Tree(13)

	#insert(t, 10)

	t.drow()


if __name__ == "__main__":
	main() 