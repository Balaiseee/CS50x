from cs50 import get_float


# Pilot code


def main():
    # Gets change from user
    change = get_positive_float()*100
    # Gets the number of quarters
    quarters = change // 25
    # Update change
    change -= quarters * 25
    # Gets the number of dimes
    dimes = change // 10
    # Update change
    change -= dimes * 10
    # Gets the number of nickels
    nickels = change // 5
    # Update change
    change -= nickels * 5
    # Gets the number of pennies
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
