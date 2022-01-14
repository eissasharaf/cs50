#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <math.h>
#include <ctype.h>

bool zcheck(char *secret);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        char *key = malloc(3 * sizeof(char));
        for (int i = 0; i < 2; i++)
        {
            key[i] = argv[1][i];
        }
        key[2] = '\0';
        char password[6] = "A";
        for (int i = 0, n = strlen(password); i < pow(52, n) + (n - 1); i++)
        {
            n = strlen(password);
            char *hash1 = crypt(password, key);
            if (!hash1)
            {
                return 1;
            }
            if (strcmp(hash1, argv[1]) != 0)
            {
                if (((isupper(password[n - 1])) && (password[n - 1] != 'Z')) || ((islower(password[n - 1])) && (password[n - 1] != 'z')))
                {
                    password[n - 1]++;
                }
                else if (password[n - 1] == 'Z')
                {
                    password[n - 1] = 'a';
                }
                else if (password[n - 1] == 'z')
                {
                    if (!zcheck(password))
                    {
                        int k = strlen(password);
                        while (password[k - 1] == 'z')
                        {
                            k--;
                        }
                        for (int f = 0; f < n - k; f++)
                        {
                            password[n - f - 1] = 'A';
                        }
                        if (password[k - 1] != 'Z')
                        {
                            password[k - 1]++;
                        }
                        else
                        {
                            password[k - 1] = 'a';
                        }
                    }
                    else
                    {
                        if (n < 5)
                        {
                            for (int j = 0; j <= n; j++)
                            {
                                password[j] = 'A';
                            }
                            i = 0;
                        }
                        else
                        {
                            printf("error\n");
                            return 1;
                        }
                    }
                }
            }
            else
            {
                printf("%s\n", password);
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}

bool zcheck(char *secret)
{
    for (int i = 0, n = strlen(secret); i < n; i++)
    {
        int f = 0;
        if (secret[i] != 'z')
        {
            return false;
        }
    }
    return true;
}
