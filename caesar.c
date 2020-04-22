#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <stdlib.h> //atoi

bool isNumber(string text);

int main(int argc, string argv[])
{
    if (argc == 2 && isNumber(argv[1])) //Check if there is an argument and if it is a number.
    {
        int key = atoi(argv[1]);
        printf("Key: %i\n", key);
        string plaintext = get_string("plaintext:  ");
        string ciphertext = plaintext;
        char *min = "abcdefghijklmnopqrstuvwxyz"; //Lowercase Alphabet
        char *maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Uppercase Alphabet
        char *e;
        int index;
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if ((plaintext[i] >= 'a' && plaintext[i] <= 'z'))
            {
                e = strchr(min, plaintext[i]);
                index = (int)(e - min); //Get the index of the character in the alphabet
                ciphertext[i] = min[(index + key) % 26]; //Caesar’s algorithm
            }
            else if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
            {
                e = strchr(maj, plaintext[i]);
                index = (int)(e - maj); //Get the index of the character in the alphabet
                ciphertext[i] = maj[(index + key) % 26];//Caesar’s algorithm
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

bool isNumber(string text) //Function that returns if the string is a number
{
    int j;
    j = strlen(text);
    while (j--)
    {
        if (text[j] >= '0' && text[j] <= '9')
        {
            continue;
        }
        return false;
    }
    return true;
}