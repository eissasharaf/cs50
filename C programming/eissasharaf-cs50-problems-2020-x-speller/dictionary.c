// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

int count = 0;
#
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    int hashed = hash(word);
    for (node *tmp = table[hashed]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0 && n == strlen(tmp->word))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashed, n;
    n = strlen(word);
    for (int i = 0; i < n && i < 3; i++)
    {
        if (word[i] == 39)
        {
            n = i;
        }
    }
    switch (n)
    {
        case 1:
            
            return (toupper(word[0]) - 65) * 26 * 26;
            break;
        case 2:
            return (toupper(word[0]) - 65) * 26 * 26 + (toupper(word[1]) - 65) * 26;
            break;
        default : 
            return (toupper(word[0]) - 65) * 26 * 26 + (toupper(word[1]) - 65) * 26 + (toupper(word[2]) - 65);
            break;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open and validate the dectionary
    FILE *finput = fopen(dictionary, "r");
    if (finput == NULL)
    {
        printf("can't open the dictionary");
        return false;
    }

    // load the dectionary to the hash table
    unsigned int hashed;
    node *tmp = malloc(sizeof(node));
    tmp->next = NULL;
    if (tmp == NULL)
    {
        return false;
    }
    fscanf(finput, "%s", tmp->word);
    do
    {
        hashed = hash(tmp->word);
        tmp->next = table[hashed];
        table[hashed] = tmp;
        tmp = malloc(sizeof(node));
        count++;
        if (tmp == NULL)
        {
            return false;
        }
    }
    while (fscanf(finput, "%s", tmp->word) != EOF);
    free(tmp);
    fclose(finput);
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
        node *tmp, *cursor;
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    
        
    }
    
    
    return true;
}
