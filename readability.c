#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int wordCounting (string text);
int letterCounting (string text);
int sentenceCounting (string text);
int index (float letters, float sentences, float words);

int main (void) {
    string text = get_string("Text : ");
    int letters = 0;
    //printf("%s\n", text);
    printf("%i letter(s) \n", letterCounting(text));
    printf("%i word(s) \n", wordCounting(text));
    printf("%i sentence(s) \n", sentenceCounting(text));
    printf("Grade %i\n", index(letterCounting(text),sentenceCounting(text), wordCounting(text)));
}

int letterCounting (string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if(isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int wordCounting (string text)
{
    int count = 1; //Because the text start with a word not a space
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if(text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int sentenceCounting (string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if(text[i] == '.')
        {
            count++;
        }
    }
    return count;
}

int index(float letters, float sentences, float words)
{
    float L = (letters/words)*100;
    float S = (sentences/words)*100;
    return round(0.0588 * L - 0.296 * S - 15.8);
}