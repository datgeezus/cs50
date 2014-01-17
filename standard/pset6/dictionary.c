/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // tolower
#include <string.h>     // strcpy

#include "dictionary.h"
#include "hashtable.h"

unsigned int nWords = 0;
Node** hashTable;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO

    return (hashSearch(hashTable, word) != NULL);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE* dict = fopen(dictionary, "r");

    if (dict != NULL)
    {
        char* word = (char*)calloc(LENGTH+1,sizeof(char));
        hashTable = hashInit();

        while(fscanf(dict, "%s", word) != EOF)
        {
            nWords++;
            hashInsert(hashTable, word);
        }
        free(word);
        fclose(dict);
        return true;
    }
    else
        return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return nWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO

    hashFree(hashTable);
    return true;
}
