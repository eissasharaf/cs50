// pset2- substitution

//library declearation
#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

//functions defines
bool validate_key(string key);
string cipher_text(string key, string plain_text);

int main(int argc, string argv[])
{
    if (argc != 2)//check only one input is entered by the user
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    if (validate_key(argv[1]) != 0)//check the key is valid 
    {
        return 1;
    }
    string plain_text = get_string("plaintext:"); //prompt the user 
    string ciphertext = cipher_text(argv[1], plain_text); //change the plaintext into cipher text
    printf("ciphertext: %s\n", ciphertext);// print the ciphertext
    
}

//validate the key 
bool validate_key(string key)
{
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isupper(key[i]) && !islower(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        for (int j = 0; j < i; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    return 0;
}

//cipher the input text
string cipher_text(string key, string plain_text)
{
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isupper(plain_text[i]))
        {
            plain_text[i] = key[(int)(plain_text[i] - 65)];
            plain_text[i] = toupper(plain_text[i]);
        }
        else if (islower(plain_text[i]))
        {
            plain_text[i] = key[plain_text[i] - 97];
            plain_text[i] = tolower(plain_text[i]);
        }
        else
        {
            plain_text[i] = plain_text[i];
        }
    }
    return plain_text;
}