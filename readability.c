#include <stdio.h> //printf
#include <cs50.h> //get_string
#include <string.h> //strlen
#include <ctype.h> //isalpha
#include <math.h> //round

int wordCounting(string text); //Function that returns the number of words in a string
int letterCounting(string text);//Function that returns the number of letters in a string
int sentenceCounting(string text);//Function that returns the number of sentences in a string
int index(float letters, float sentences, float words); //Function that returns the grade of the Coleman-Liau index of a string

int main(void)
{
    string text = get_string("Text : ");
    int letters = 0;
    int grade = index(letterCounting(text), sentenceCounting(text), wordCounting(text));
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int letterCounting(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i])) //Check if the char text[i] is an alphanumeric char
        {
            count++;
        }
    }
    return count;
}

int wordCounting(string text)
{
    int count = 1; //Because the text never end with a space
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int sentenceCounting(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int index(float letters, float sentences, float words)
{
    float L = letters / words * 100;
    float S = sentences / words * 100;
    return round(0.0588 * L - 0.296 * S - 15.8);
}