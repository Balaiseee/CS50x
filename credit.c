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
    bool wrote = false;
    num = get_long("Number:"); //Get the height
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
        if (first_digit(numCopy,2) == 34 && round(log10(numCopy)) == 15) {printf("AMEX\n"); wrote = true;}
        if (first_digit(numCopy,2) == 37 && round(log10(numCopy)) == 15) {printf("AMEX\n"); wrote = true;}
        if (first_digit(numCopy,1) == 4 && (round(log10(numCopy)) == 13 || round(log10(numCopy)) == 16) ) {printf("VISA\n"); wrote = true;}
        if (first_digit(numCopy,2) == 51 && round(log10(numCopy)) == 16) {printf("MASTERCARD\n");}
        if (first_digit(numCopy,2) == 52 && round(log10(numCopy)) == 16) {printf("MASTERCARD\n"); wrote = true;}
        if (first_digit(numCopy,2) == 53 && round(log10(numCopy)) == 16) {printf("MASTERCARD\n"); wrote = true;}
        if (first_digit(numCopy,2) == 54 && round(log10(numCopy)) == 16) {printf("MASTERCARD\n"); wrote = true;}
        if (first_digit(numCopy,2) == 55 && round(log10(numCopy)) == 16) {printf("MASTERCARD\n"); wrote = true;}
        if (wrote == false) {printf("INVALID\n"); wrote = true;}
    } else if (wrote == false)
    {
        printf("INVALID\n");
    }

}
