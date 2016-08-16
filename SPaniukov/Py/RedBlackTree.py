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

def insert(root):
	assert root.is_valid

	node = BTA.insert(root)

	assert root.is_valid

def create_rbtree():
	pass

def main():
	t = Tree(13)

	#insert(t, 10)

	t.drow()


if __name__ == "__main__":
	main() 