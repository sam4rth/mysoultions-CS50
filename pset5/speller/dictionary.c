// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void killer(struct node *n);

//File pointer
FILE *f;

//Size
unsigned int ssize = 0;

// Buffer
char b[LENGTH + 1];


// Number of buckets in hash table
const unsigned int N = 17000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int i = hash(word);

    node *c = table[i];


    while (c != NULL)
    {
        if (strcasecmp(c->word, word) == 0)
        {
            return true;
        }
        else
        {
            c = c->next;
        }
    }

    return false;
}


// This function is implimented by me but the idea is from the internet.
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))        // *str++ is going to the next address in memory, where the next char in the string is stored
    {
        if (isupper(c))
        {
            c = c + 32;
        }

        hash = ((hash << 5) + hash) + c; // hash * 33 + c   // hash << 5 = hash * 2^5
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    node *temp = NULL;
    node *tem = NULL;
    unsigned int hi;

    f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    // This gets word by word from the file
    while (fscanf(f, "%s", b) != EOF)
    {
        temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy((*temp).word, b);
        temp->next = NULL;

        hi = hash(b);

        // this adds the new word to the start of the linklist
        temp->next = table[hi];
        table[hi] = temp;
        ssize++;
        temp = NULL;

    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return ssize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            killer(table[i]);
        }
    }
    return true;
}

void killer(struct node *n)
{
    if (n == NULL)
    {
        free(n);
        return;
    }

    killer(n->next);
    free(n);
    return;
}
