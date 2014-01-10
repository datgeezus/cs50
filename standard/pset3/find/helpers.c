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
        return binary_search(value, values, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    selection_sort(values, n);
    return;
}

// Custom search functions
bool linear_search(int value, int values[], int n)
{
    for (int i = 0; i < n; i++)
        if (values[i] == value)
            return true;

    return false;
}

bool binary_search(int value, int values[], int n)
{
    int ending = n-1;
    int beggining = 0;

    while (ending >= beggining)
    {
        int middle = (beggining + ending) / 2;
        if (values[middle] == value)
            return true;
        else if (values[middle] > value)
            ending = middle - 1;
        else
            beggining = middle + 1;
    }

    return false;
}

// Custom sort functions
void bubble_sort(int values[], int n)
{
    bool iter;

    do
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
    } while (iter);
    return;
}

void selection_sort(int values[], int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        int smallest_index = i;
        for (int j = i+1; j < n; j++)
        {
            if (values[smallest_index] > values[j])
                smallest_index = j;
        }
        // Swap values;
        temp = values[smallest_index];
        values[smallest_index] = values[i];
        values[i] = temp;
    }
}
