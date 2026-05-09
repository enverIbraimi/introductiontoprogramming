#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Table node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose a large prime or power of 2 for N to minimize collisions
const unsigned int N = 26; 
node *table[N];
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to get index
    int index = hash(word);

    // Access linked list at that index
    node *cursor = table[index];

    // Traverse linked list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number (Sample: First letter)
unsigned int hash(const char *word)
{
    // For better speed, you could sum ASCII values or use a DJB2 hash
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) return false;

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) return false;

        strcpy(new_node->word, word);
        
        // Hash word
        int index = hash(word);

        // Insert node into hash table (Prepend to list)
        new_node->next = table[index];
        table[index] = new_node;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}