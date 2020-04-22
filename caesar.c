#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> //isdigit isalpha
#include <stdlib.h>
#include <string.h>

bool isNumber(string text);

int main(int argc, string argv[])
{
    if(argc == 2 && isNumber(argv[1]))
    {
        int key = atoi(argv[1]);
        printf("Key: %i\n", key);
        string plaintext = get_string("plaintext:  ");
        string ciphertext = plaintext;
        for (int i = 0, n = strlen(plaintext); i< n; i++)
        {
            if ((plaintext[i] >= 'a' && plaintext[i] <= 'z') || (plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
            {
                if(tolower(plaintext[i]-97)<key)
                {
                    ciphertext[i] = plaintext[i]+key;   
                }
                else
                {
                    ciphertext[i] = plaintext[i]-key;
                }
            }
            else
            {
                ciphertext[i] = plaintext[i];
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

bool isNumber(string text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(text[j] >= '0' && text[j] <= '9')
            continue;

        return false;
    }
    return true;
}