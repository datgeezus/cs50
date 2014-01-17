#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"


Node** hashInit()
{
    // Create a hash table
    Node** hashTable = (Node **)calloc(TABLE_SIZE, sizeof(Node *));   // Array of pointers to Nodes

    return hashTable;
}


void hashInsert(Node** hashTable, char* word)
{
    /**
     * There are no repeated words in the dictionary, so it is not necessary
     * to search if the word is already stored.
     */

    // get a new hash value
    uint32_t hash = hashFunction(word, TABLE_SIZE, SEED);

    // Create a new node on the heap and store the word
    Node* newNode = (Node *)calloc(1, sizeof(Node));
    strcpy(newNode->word, word);

    // Store the new node on the hash table
    if (hashTable[hash] == NULL)    // if this is the first node
    {
        hashTable[hash] = newNode;
    }
    else    // Put it on the front
    {
        newNode->next = hashTable[hash];
        hashTable[hash] = newNode;
    }
}

Node* hashSearch(Node** hashTable, const char* word)
{
    // Get a new hash value
    uint32_t hash = hashFunction(word, TABLE_SIZE, SEED);

    // Traverse each node
    Node* cursor = hashTable[hash];

    while (cursor != NULL && hashCompareValues(cursor->word, word) != 0)
        cursor = cursor->next;

    return cursor;
}

uint32_t hashFunction(const char* word, uint32_t tableSize, uint32_t seed)
{

    char    c;
    unsigned int h;

    h = seed;
    for( ; ( c = *word)!='\0' ; word++ )
    {
    h ^= ( (h << 5) + (c | TOLOWER) + (h >> 2) );
    }
    return((unsigned int)((h&0x7fffffff) % tableSize));
}

void hashFree(Node** hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* cursor = hashTable[i];
        while (cursor != NULL)
        {
            Node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    free(hashTable);
}

uint32_t hashCompareValues( const char* s1, const char* s2 )
{
    while ( *s1 != 0 && ((*s1) | TOLOWER) == ((*s2) | TOLOWER))
    {
        s1++;
        s2++;
    }
    return *s1-*s2;
}

// for( hprv = NULL, htmp=ht[hval] ; htmp != NULL && scmp(htmp->word, w) != 0 ; hprv = htmp, htmp = htmp->next )
//     {
//     ;
//     }
