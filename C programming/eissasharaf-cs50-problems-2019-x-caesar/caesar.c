#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{   
    if (argc == 2)
    {
        int p = 0, n = strlen(argv[1]);
        for (int i = 0 ; i < n; i++)
        {     
            if (argv[1][i] >= 48 & argv[1][i] <= 57)
            {  
                p++;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                break;
                return 1;
            }
        }
        if (p == n)
        {
            int k = atoi(argv[1]);
            string plaintext = get_string("plaintext: ");
            for (int j = 0, q = strlen(plaintext); j < q; j++)
            {
                if (islower(plaintext[j]))
                {
                    plaintext[j] -= 97;
                    plaintext[j] = (plaintext[j] + k) % 26;
                    plaintext[j] += 97;
                }
                else if (isupper(plaintext[j]))
                {
                    plaintext[j] -= 65;
                    plaintext[j] = (plaintext[j] + k) % 26;
                    plaintext[j] += 65;
                }
            }
            printf("ciphertext: %s\n", plaintext);
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
/*                if (islower(plaintext[j]) || isupper(plaintext[j]))
                {
                    for (int w = 0; w < k; w++)
                    {
                        if (plaintext[j] != 122 & plaintext[j] != 90)
                        {
                            plaintext[j]++;
                        }
                        else
                        {
                            plaintext[j] -= 25;
                        }  
                    }
                }    
                */
