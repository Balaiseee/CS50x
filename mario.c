#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height?"); //Get the height
    if((height >= 1) && (height <= 8))
    {
        for (int i = 1; i <= height; i++)
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
