class Tree:
    #constructor: explicit this -> self
    def __init__(self, data, left=None, right=None):
        # assert isinstance(left, Tree)
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)

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

def get_height_my(tree):
    if not tree :
        return

    next_Level = []
    for x in tree :
        if x.left :
            next_Level.append(x.left)
        if x.right :
            next_Level.append(x.right)

    get_height(next_Level)

    print("RES = " + str(len(next_Level)))
    return len(next_Level)

def get_height(tree):
    if not tree:
        return 0

    return 1 + max(get_height(tree.left), get_height(tree.right))
    
def main():
    t = create_tree()

    print("HEIGHT = " + str(get_height(t)))


if __name__ == '__main__':
    main()

