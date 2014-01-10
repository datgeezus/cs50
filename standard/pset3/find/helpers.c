/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (value < 0)
        return false;
    else
        return linear_search(value, values, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    bubble_sort(values, n);
    return;
}

// Custom functions
bool linear_search(int value, int values[], int n)
{
    for (int i = 0; i < n; i++)
        if (values[i] == value)
            return true;

    return false;
}

void bubble_sort(int values[], int n)
{
    bool iter = true;
    while (iter)
    {
        iter = false;
        for (int i = 0; i < n-1; i++)
        {
            if (values[i] > values[i+1])
            {
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                iter = true;
            }
        }
    }
    return;
}
