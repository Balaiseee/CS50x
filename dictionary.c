// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
   char lower_word[LENGTH + 1];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';
    node *tmp = table[hash(lower_word)];
    while(tmp != NULL)
    {
        if (strcasecmp(tmp->word, lower_word) == 0)
        {
            return true;
        } else {
            tmp = tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    for(int c = 0; word[c] != '\0'; c++)
        hash = ((hash << 5) + hash) + c;
    return hash % N;
}
int word_count = 0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Scans dictionary word by word (populating hash table with nodes containing words found in dictionary)
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Mallocs a node for each new word (i.e., creates node pointers)
        node *new_node = malloc(sizeof(node));
        // Checks if malloc succeeded, returns false if not
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // Copies word into node if malloc succeeds
        strcpy(new_node->word, word);

        // Initializes & calculates index of word for insertion into hashtable
        int h = hash(new_node->word);

        // Initializes head to point to hashtable index/bucket
        node *head = table[h];

        // Inserts new nodes at beginning of lists
        if (head == NULL)
        {
            table[h] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = table[h];
            table[h] = new_node;
            word_count++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *cursor = head;
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    return true;
}