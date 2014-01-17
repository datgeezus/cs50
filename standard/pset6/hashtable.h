#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

// to avoid collison with dictionary.h definition
#ifndef LENGTH
#define LENGTH 45
#endif

#define TABLE_SIZE  4096         // Hashtable size
#define SEED        48151623    // Used in the Zobel algorithm

#define TOLOWER     (char)0x20        // Mask to pass only left most 5 bits

typedef struct Node
{
    char word[LENGTH + 1];   // word stored in each node + \0
    struct Node* next;
} Node;

Node** hashInit(void);
void hashInsert(Node** hashTable, char* word);
Node* hashSearch(Node** hashTable, const char* word);
uint32_t hashCompareValues(const char* s1, const char* s2);
uint32_t hashFunction(const char* word, uint32_t size, uint32_t seed);
void hashFree(Node** hashTable);

#endif // HASHTABLE_H
