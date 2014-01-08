#include <stdio.h>
#include <math.h>
#include <cs50.h>

// Coin constants
#define QUARTER 25
#define DIME    10
#define NICKEL  5
#define PENNY   1

int main(void)
{
    float change = 0;
    do
    {
        // Prompt user for the amount of owed change
        printf("Owed change: $ ");
        change = GetFloat();
    }
    while (change < 0.0);               // Allow only positive values
    
    // Convert to cents
    int cents = round(change * 100);
    
    // numbers of coins used
    int nCoins = 0;
    
    
    while (cents > 0)
    {
        if (cents >= QUARTER)
        {
            nCoins += cents / QUARTER;
            //printf("%d quartes.\n", cents / QUARTER);
            cents -= QUARTER * (cents / QUARTER);
        }
        else if (cents >= DIME)
        {
            nCoins += cents / DIME;
            //printf("%d dimes.\n", cents / DIME);
            cents -= DIME * (cents / DIME);
        }
        else if (cents >= NICKEL)
        {
            nCoins += cents / NICKEL;
            //printf("%d nickels.\n", cents / NICKEL);
            cents -= NICKEL * (cents / NICKEL);
        }
        else
        {
            nCoins += cents;
            //printf("%d pennies.\n", cents / PENNY);
            cents = 0;
        }
    }
    
    // Print number of coins used
    printf("%d\n", nCoins);
    return 0;
}
