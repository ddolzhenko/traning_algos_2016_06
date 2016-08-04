


# functions
def main():
    print("hell'o w'orld")
    print('hell"o w"orld')

# function call
main()

def main():
    print("hell on world")

main()

# return function
def get_main():
    def main():
        print("hello ????")
    return main

m = get_main()

m()

# will work only in MAIN module
if __name__ == '__main__':
    main()

# name of module
import os
print(os.__name__)