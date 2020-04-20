#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change; //Declare the variable
    int coins = 0; //Initializes coins to 0
    do
    {
        change = get_float("Change owed:"); //Get the height
    }
    while (!(change >= 0)); //Re ask for the height if value < 0
    int cents = round(change * 100);
    coins += round(cents / 25);
    cents -= round(cents / 25) * 25;
    coins += round(cents / 10);
    cents -= round(cents / 10) * 10;
    coins += round(cents / 5);
    cents -= round(cents / 5) * 5;
    coins += round(cents);
    printf("%d", coins);
}
