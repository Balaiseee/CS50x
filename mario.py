from cs50 import get_int

# Pilot code


def main():
    i = get_positive_int()
    # Manages the display of the pyramid
    for c in range(1, i + 1):
        print((i - c) * " " + c * "#" + "  " + c * "#")

# Sanitizes the inputs to get a positive integer between 1 and 8


def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n


main()
