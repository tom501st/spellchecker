// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int count;

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
bool check(const char *word1)
{
    // 1. get word's hash value
    // 2. go into linked list and find the word using strcasecmp
    int index = hash(word1);
    for (node* cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if(strcasecmp(cursor->word, word1) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) // source: David Emily, YouTube
{
    int value = 0;
    for(int i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // 1.open dictionary file
    FILE* dicload = fopen(dictionary ,"r");
    if (dicload == NULL)
    {
        printf("dictionary failed to load\n");
        return false;
    }

    // 2.read strings from file one at a time
    char newword[LENGTH + 1];
    while (fscanf(dicload, "%s\n", newword) != EOF)
    {
        // 3.create new node for each word
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // store word into node
        strcpy(n->word, newword);

        if(strstr(n->word, newword) == NULL)
        {
            return false;
            return 1;
        }

        // 4.hash word to obtain hash value
        int index = hash(newword);

        // 5.insert node into hash table at that location

        if(table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        if(table[index] == NULL)
        {
            return false;
        }
        if(strcmp(table[index]->word, newword) == 0)
        {
            count ++;
        }
    }
    fclose(dicload);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)            // while list is not empty
        {
            node *tmp = table[i]->next;     // create node* tmp which sits at the node after list
            free(table[i]);                 // free the node before it (list)
            table[i] = tmp;                 // move 'list' up one
        }
    }

    for(int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        if(cursor != NULL)
        {
            return false;
        }
    }
    return true;
}
