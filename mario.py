from cs50 import get_int

def main():
    i = get_positive_int()
    for c in range(1, i + 1):
        print((i - c) * " " + c * "#")

def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n > 0:
            break
    return n

main()