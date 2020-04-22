#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> //toupper & tolower
bool isLetter(string text); //Function that returns true if the string contains only letters
bool isUnique(string text); //Function that returns true if the string contains only unique elements
char* upperCase(char* arr); //Function that puts an array of char in uppercase
char* lowerCase(char* arr); //Function that puts an array of char in lowercase

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!isLetter(argv[1]))
    {
        return 1;
    }
    else if (!isUnique(argv[1]))
    {
        return 1;
    }
    else
    {
        char* key = argv[1];
        printf("Key: %s\n", key);
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
                char *keymin = lowerCase(key); //Lowercase Key
                ciphertext[i] = keymin[(index) % 26]; //Substitution’s algorithm
            }
            else if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
            {
                e = strchr(maj, plaintext[i]);
                index = (int)(e - maj); //Get the index of the character in the alphabet
                char *keymaj = upperCase(key); //Uppercase Alphabet
                ciphertext[i] = keymaj[(index) % 26];//Substitution’s algorithm
            }
        }
        printf("ciphertext: %s\n", ciphertext);
    }
}

char* upperCase(char* arr)
{
    int i = 0;
    char *str = arr;

    while(str[i])
    {
        str[i] = toupper(arr[i]);
        i++;
    }
    return str;
}
char* lowerCase(char* arr)
{
    int i = 0;
    char *str = arr;

    while(str[i])
    {
        str[i] = tolower(arr[i]);
        i++;
    }
    return str;
}
bool isLetter(string text) //Function that returns true if the string contains only letters
{
    int j = strlen(text);
    while (j--)
    {
        if ((text[j] >= 'A' && text[j] <= 'Z') || (text[j] >= 'a' && text[j] <= 'z'))
        {
            continue;
        }
        return false;
    }
    return true;
}
bool isUnique(string text) //Function that returns true if the string contains only unique elements
{
    int size = strlen(text);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if(text[i] == text[j])
            {
                return false;
            }
        }
    }
    return true;
}