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
int first_digit(long num, int nb)
{
  	int Count = log10(num);
  	int FirstDigit = num / pow(10, Count-nb+1);
    return FirstDigit;
}

int main(void)
{
    long num;
    int count = 0;
    int sumOdd = 0;
    int sumEven = 0;
    long numCopy;
    num = get_long("Number:"); //Get the height
    if (log10(num) != 13 && log10(num) != 15 && log10(num) != 16) {goto END;}
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
        if (first_digit(numCopy,2) == 34) {printf("AMEX\n");}
        if (first_digit(numCopy,2) == 37) {printf("AMEX\n");}
        if (first_digit(numCopy,1) == 4) {printf("VISA\n");}
        if (first_digit(numCopy,2) == 51) {printf("MASTERCARD\n");}
        if (first_digit(numCopy,2) == 52) {printf("MASTERCARD\n");}
        if (first_digit(numCopy,2) == 53) {printf("MASTERCARD\n");}
        if (first_digit(numCopy,2) == 54) {printf("MASTERCARD\n");}
        if (first_digit(numCopy,2) == 55) {printf("MASTERCARD\n");}
    } else
    {
        END:printf("INVALID\n");
    }
}
