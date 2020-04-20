#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("What is your name?\n"); //Get the height
    if(!(height <= 0))
    {
        for (int i = 0; i <= height; i++)
        {
            for (int j = height-i-1; j >= 0 ; j--)
            {
                printf(" ");
            }
            for (int j = 0 ; j < i ; j++)
            {
                printf("#");
            }
            printf("\n");
        //printf("Height: %d\n", height); //Print the name
     }
    }
}
