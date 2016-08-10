#import tree
#from tree import Tree

import binaryTreesAlgorithms as BTA
from binaryTreesAlgorithms import Tree

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

def create_tree_3():
	t = Tree(13)
	for x in range(1, 10):
		insert(t, x)
	return t

def create_tree_4():
	t = Tree(46)
	import random
	arr = list(range(1, 80))
	random.shuffle(arr)
	for x in arr:
		insert(t, x)
	return t

def main():
	
	t = create_tree()

	BTA.dfs_pre_order(t)
	
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
	for x in BTA.dfs_pre_order_imperative(t):
		print(x)
	t.draw()

	t = create_tree()

	BTA.insert(t, 12)
	BTA.insert(t, 56)
	BTA.insert(t, -23)
	BTA.insert(t, 10)

	print (list(map(str, BTA.dfs_in_order(t))))
	print (list(map(str, BTA.iterate_forward(t))))
	BTA.remove(BTA.find(t, 25))
	print (list(reversed(list(map(str, BTA.iterate_backward(t))))))
	print (BTA.find(t, 10))
	t.draw()
	

if __name__ == '__main__':
	main()