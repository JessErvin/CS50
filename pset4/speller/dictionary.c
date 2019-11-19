// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Initialize a wordcounter
int wordCount = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Hash the word
        unsigned int hashValue = hash(word);


        // Allocate space for the word and point to it with wordNode
        node *wordNode = malloc(sizeof(node));

        // Free all memory if there is no space
        if (wordNode == NULL)
        {
            fclose(file);
            return false;
        }

        // Insert the word into the node
        strcpy(wordNode -> word, word);

        // Add the node
        wordNode -> next = hashtable[hashValue];
        hashtable[hashValue] = wordNode;

        // add word to wordCount
        wordCount++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Count the words while interating through the dictionary. No need to count twice.
    if (wordCount > 0)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to check
    unsigned int hashValue = hash(word);

    // Set a pointer
    node *cursor = hashtable[hashValue];

    // Compare the input word to each word in the dictionary
    while (cursor != NULL)
    {
        // If we find the word (ignoring upper & lower case) return true
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        else
        {
            // Move on to the next one
            cursor = cursor -> next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {

            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;

}
