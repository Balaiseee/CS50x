#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#define ALPHABET_LENGTH 26

//Define trie_node & trie_tree
struct trie_node
{
    bool is_leaf;
    struct trie_node *children[ALPHABET_LENGTH];
};

typedef struct trie_node *trie_tree;

//Global variables
unsigned int words = 0;
trie_tree head = NULL;

//Prototypes
trie_tree trie_create(void);
bool trie_insert(trie_tree root, const char *key);
bool trie_find(trie_tree root, const char *key);
void trie_free(trie_tree root);



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return trie_find(head, word);
}

unsigned int hash(const char letter)
{
    if(letter == '\'')
    {
        return ALPHABET_LENGTH-1;
    }
    //Ignore case by converting the given letter to lowercase
    return tolower(letter) - 97;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE * dict = fopen(dictionary, "r");

    // Check that dictionary could be opened
    if (dict == NULL)
    {
        printf("Dictionary does not exist.\n");
        return false;
    }
    head = trie_create();
    if(head == NULL)
    {
        return false;
    }
    char buffer[LENGTH];
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        if (!trie_insert(head, buffer))
        {
            unload();
            break;
        }

        words++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    trie_free(head);
    return true;
}

trie_tree trie_create(void)
{
    trie_tree node = malloc(sizeof(struct trie_node));
    //Insufficient memory
    if (node == NULL)
    {
        return NULL;
    }
    //A new node is not a leaf node by default
    node->is_leaf = false;
    //Initialize children pointers to NULL
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

bool trie_insert(trie_tree root, const char *key)
{
    trie_tree node = root;
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        unsigned int h = hash(key[i]);
        // create new node if necessary
        if (node->children[h] == NULL)
        {
            node->children[h] = trie_create();
        }
        node = node->children[h];
        //Insufficient memory
        if (!node)
        {
            return false;
        }
    }
    node->is_leaf = true;
    return true;
}
bool trie_find(trie_tree root, const char *key)
{
    trie_tree node = root;
    for (int i = 0, length = strlen(key); i < length; i++) {
        unsigned int h = hash(key[i]);
        //Nonexistent node
        if (node->children[h] == NULL) {
            return false;
        }
        node = node->children[h];
        //Insufficient memory
        if (!node) {
            return false;
        }
    }
    return node->is_leaf;

}
void trie_free(trie_tree root)
{
    //End statement
    if (root == NULL) {
        return;
    }
    for (int i = 0 ; i < ALPHABET_LENGTH; i++) {

        trie_free(root->children[i]);
    }
    free(root);
}