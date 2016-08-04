
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
    dfs_pre_order(t, print)
    print("****************************")
    dfs_in_order(t, print)
    print("****************************")
    dfs_post_order(t, print)
    print("****************************")

if __name__ == '__main__':
	main()