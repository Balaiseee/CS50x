#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> //isdigit isalpha
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc == 2 && (atoi(argv[1])))
    {
        int key = atoi(argv[1]);
        printf("Key: %i\n", key);
        string plaintext = get_string("plaintext:  ");
        string ciphertext = plaintext;
        for (int i = 0, n = strlen(plaintext); i< n; i++)
        {
            if (isalpha(plaintext[i]))
            {
                ciphertext[i] = plaintext[i] + key % 26;
            }
        }
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}