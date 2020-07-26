from cs50 import get_float


# Pilot code


def main():
    change = get_positive_float()*100
    quarters = change // 25
    change -= quarters * 25
    dimes = change // 10
    change -= dimes * 10
    nickels = change // 5
    change -= nickels * 5
    pennies = change
    print(round(quarters+dimes+nickels+pennies))


# Sanitizes the inputs to get a positive integer


def get_positive_float():
    while True:
        n = get_float("Change owed: ")
        if n > 0:
            break
    return n


main()
