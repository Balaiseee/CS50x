#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h>
bool isNumber(string text);
char* upperCase(char* arr);
char* lowerCase(char* arr);
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
                char *keymin = lowerCase(key);
                ciphertext[i] = keymin[(index) % 26]; //Caesar’s algorithm
            }
            else if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
            {
                e = strchr(maj, plaintext[i]);
                index = (int)(e - maj); //Get the index of the character in the alphabet
                char *keymaj = upperCase(key);
                ciphertext[i] = keymaj[(index) % 26];//Caesar’s algorithm
            }
        }
        printf("ciphertext: %s\n", ciphertext);
    }
}

char* upperCase(char* arr)
{
    int i = 0;
    char c;
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
    char c;
    char *str = arr;
	
    while(str[i])
    {
        str[i] = tolower(arr[i]);
        i++;
    }
    return str;
}