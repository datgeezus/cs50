#include <stdio.h>
#include <stdlib.h>     // atoi (also on cs50.h)
#include <cs50.h>       // string data type
#include <string.h>     // strlen
#include <ctype.h>      // isupper, islower

char VigenereCipher(char, int);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <keyword>\n", argv[0]);
        return 1;
    }
    else
    {
        string k = argv[1];
        for (int i = 0; i < strlen(k); i++)
            if (!isalpha(k[i]))
            {
                printf("Keyword must only contain letters A-Z and a-z\n");
                return 1;
            }

        int mod_k = strlen(k);
        string message = GetString();

        for (int i = 0, j = 0; i < strlen(message); i++)
        {
            if (isalpha(message[i]))
            {
                message[i] = VigenereCipher(message[i], k[j % mod_k]);
                j++;
            }
        }

        printf("%s\n", message);
        return 0;
    }
}


char VigenereCipher(char p, int k)
{
    k = tolower(k) - 'a';
    if (isupper(p))
        return (((p - 'A') + k) % 26) + 'A';
    else
        return (((p - 'a') + k) % 26) + 'a';
}
