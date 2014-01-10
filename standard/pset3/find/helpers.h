/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

// Custom sort functions
// bool linear_search(int value, int values[], int n);
bool binary_search(int value, int values[], int n);

// Custom search functions (uncomment just one)
// void bubble_sort(int values[], int n);
void selection_sort(int values[], int n);
// static void insertion_sort(int values[], int n);
