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
        char *min = "abcdefghijklmnopqrstuvwxyz";
        char *maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char *e;
        int index;
        for (int i = 0, n = strlen(plaintext); i< n; i++)
        {
            if ((plaintext[i] >= 'a' && plaintext[i] <= 'z'))
            {
                e = strchr(min, plaintext[i]);
                index = (int)(e - min);
                if(strlen(min)< index+key)
                {
                    ciphertext[i] = min[index+key-strlen(min)];    
                }
                else
                {
                    ciphertext[i] = min[index+key];
                }
            }
            else if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
            {
                e = strchr(maj, plaintext[i]);
                index = (int)(e - maj);
                if(strlen(maj)< index+key)
                {
                    ciphertext[i] = maj[index+key-strlen(maj)];    
                }
                else
                {
                    ciphertext[i] = maj[index+key];
                }
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