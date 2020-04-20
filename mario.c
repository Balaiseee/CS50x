#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height; //Declare the variable
    do
    {
        height = get_int("Height?"); //Get the height
    }
    while (!(height >= 1) || !(height <= 8)); //Re ask for the height if value is not between 1 and 8
    {
        for (int i = 1; i <= height; i++)
        {
            for (int j = height - i - 1; j >= 0 ; j--) //Loops for the space
            {
                printf(" ");
            }
            for (int j = 0 ; j < i ; j++) //Loops for the '#'
            {
                printf("#");
            }
            printf("\n");
        }
    }
}
