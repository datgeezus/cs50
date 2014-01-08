#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    long long ccNumber = 0;
    do
    {
        printf("Number: ");
        ccNumber = GetLongLong();
    }
    // Minimum number is a 13 digit VISA starting with 4
    // Maximum number is a 16 digit MASTERCARD starting with 55
    while(ccNumber < 4e12 && ccNumber > 5.5e15);
    
    // Count number of digits
    int nDigits = 0;
    long long n = ccNumber;
    while (n !=0 )
    {
        n /= 10;
        nDigits++;
    }
    
    int ccDigits[nDigits];
    int evenSum = 0, oddSum = 0, totalSum = 0;
    n = ccNumber;
    for (int i = nDigits-1; i >=0 ; i--)
    {
        ccDigits[i] = n % 10;
        n /= 10;
        if ((i+1) % 2 == 0)
        {
            int tempDig = ccDigits[i] * 2;
            if (tempDig < 10) oddSum += tempDig;
            else
            {
                oddSum += tempDig % 10;
                oddSum += tempDig / 10;
            }
            
        }
        else
        {
            evenSum += ccDigits[i];
        }
    }
    
    totalSum = evenSum + oddSum;
    
    printf("nDigits: %d\n", nDigits);
    printf("odd: %d\n", oddSum);
    printf("even: %d\n", evenSum);
    printf("total: %d\n", totalSum);
    
    
    short cardFound = totalSum % 10;
    if (0 == cardFound)
    {
        switch(ccDigits[0])
        {
            case (3):   // AMEX
                if (4 == ccDigits[1] ||
                    7 == ccDigits[1]) printf("AMEX\n");
                else printf("INVALID\n");
                break;
            case (5):   // MASTERCARD
                if (1 == ccDigits[1] || 
                    2 == ccDigits[1] ||
                    3 == ccDigits[1] ||
                    4 == ccDigits[1] ||
                    5 == ccDigits[1])  printf("MASTERCARD\n");
                else printf("INVALID\n");
                break;
            case (4):   // VISA
                printf("VISA\n");
                break;
            default:    // INVALID
                printf("INVALID\n");
                break;
                
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
    
    return 0;
}
