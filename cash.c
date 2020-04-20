#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change; //Declare the variable
    do
    {
        change = get_float("Change owed:"); //Get the height
    }
    while (!(change >= 0) || !(change <= 1)); //Re ask for the height if value is not between 0 and 1
    int cents = round(change * 100);
    int coins = 0;
    coins += round(cents/25);
    cents -= round(cents/25)*25;
    coins += round(cents/10);
    cents -= round(cents/10)*10;
    coins += round(cents/5);
    cents -= round(cents/5)*5;
    coins += round(cents/1);
    printf("%d", coins);
}
