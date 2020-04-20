#include <cs50.h>
#include <stdio.h>
#include <math.h>
int sum_digit(int num)
{
    int sum = 0;
    while(num != 0)
    {
        int digit = num % 10;
        num = num / 10;
        sum += digit;
    }
    return sum;
}

int main(void)
{
    long num;
    int count = 0;
    int sumOdd = 0;
    int sumEven = 0;
    NUM:do
    {
        num = get_long("Number:"); //Get the height
    }
    while (num < 0); //Re ask for the height if value < 0
    while(num != 0)
    {
        if (count%2==1)
        {
            sumEven += sum_digit((num%10)*2);
        }
        if (count%2==0)
        {
            sumOdd += sum_digit(num%10);
        }
        int digit = num % 10;
        num = num / 10;
        count++;
    }
    if (count != 16) {count = 0; goto NUM;}
    if((sumEven+sumOdd)%10==0)
    {
        printf("VISA\n");
    }
}
