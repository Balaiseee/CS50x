// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Sanitizes word (makes the word lowercase)
    char lower_word[LENGTH + 1];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';
    // Goes to his bucket
    node *tmp = table[hash(lower_word)];
    // Browses the linked list
    while (tmp != NULL)
    {
        //If the word is contained in one of the nodes returns true else goes to the next node
        if (strcasecmp(tmp->word, lower_word) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    for (int c = 0; word[c] != '\0'; c++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}
int word_count = 0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Scans dictionary line by line (here word by word)
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Creates node pointers for each new word (allocates memory and initializes it to a universal zero value to avoid valgrind error as opposed to malloc just allocating memory)
        node *new_node = calloc(1,sizeof(node));
        // Checks if malloc succeeded
        if (new_node == NULL)
        {
            return false;
        }
        // Copies word into node
        strcpy(new_node->word, word);

        // Index of word for insertion into hashtable
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
    // Browses each bucket
    for (int i = 0; i < N; i++)
    {
        // Frees the associated linked list
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}