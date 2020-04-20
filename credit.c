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
int first_digit(long num)
{
  	int Count = log10(num);
  	int FirstDigit = num / pow(10, Count);
    return FirstDigit;
}

int main(void)
{
    long num;
    int count = 0;
    int sumOdd = 0;
    int sumEven = 0;
    long numCopy;
    do
    {
        num = get_long("Number:"); //Get the height
    }
    while (num < 0 && log10(num) != 15); //Re ask for the height if value < 0
    numCopy = num;
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
        count++;
        int digit = num % 10;
        num = num / 10;
    }
    if((sumEven+sumOdd)%10==0)
    {
        if (first_digit(numCopy) == 3) {printf("AMEX\n");}
        if (first_digit(numCopy) == 4) {printf("VISA\n");}
        if (first_digit(numCopy) == 5) {printf("MASTERCARD\n");}
    } else
    {
        printf("INVALID\n");
    }
}
