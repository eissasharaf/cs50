#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int shift(char c);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int p = 0, n = strlen(argv[1]);
        for (int i = 0 ; i < n; i++)
        {     
            if (isupper(argv[1][i]) || islower(argv[1][i]))
            {  
                p++;
            }
            else
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
                break;
            }
        }
        if (p == n)
        {
            int key[n];
            for (int x = 0; x < n; x++)
            {
                key[x] = shift(argv[1][x]); 
            }
            string plaintext = get_string("plaintext: ");
            int q = strlen(plaintext);
            int ciphertext[q];
            int t[q];
            for (int y = 0; y < q; y++)
            {
                ciphertext[y] = shift(plaintext[y]); 
                if (isupper(plaintext[y]))
                {
                    t[y] = 1;
                }
                else if (islower(plaintext[y]))
                {
                    t[y] = 2;
                }
                else
                {
                    t[y] = 0;
                }
            }
            int r = 0;
            for (int e = 0; e < q; e++)
            {
                if (t[e] == 1 || t[e] == 2)
                {
                    ciphertext[e] = (ciphertext[e] + key[r]) % 26;
                    r++;
                    if (r == n)
                    {
                        r = 0; 
                    }
                    if (t[e] == 1)
                    {
                        ciphertext[e] += 65;
                    }
                    else if (t[e] == 2)
                    {
                        ciphertext[e] += 97;
                    }
                }
            }
            printf("ciphertext: ");
            for (int o = 0; o < q; o++)
            {
                printf("%c", ciphertext[o]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
      
    }
}  


int shift(char c)
{
    if (isupper(c))
    {
        return c - 65;
    }
    else if (islower(c))
    {
        return c - 97;    
    }
    else
    {
        return c;
    }
}
