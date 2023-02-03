#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];

    string basic = "abcdefghijklmnopqrstuvwxyz";

    bool nonAlpha = false;
    bool repeats = false;

    if(argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for(int i = 0; i < strlen(key); i++)
    {
        if(!isalpha(key[i]))
        {
            nonAlpha = true;
        }

        int count = 0;

        for(int j = 0; j < strlen(key); j++)
        {
            if(key[i] == key[j])
            {
                count++;
            }

        }

        if(count > 1)
        {
            repeats = true;
        }

        count = 0;
    }

    if(repeats)
    {
        printf("Key must not containe repeated characters.\n");
        return 1;
    }

    if(nonAlpha)
    {
        printf("Key must only containe alphabetic characters.\n");
        return 1;
    }

    string plaintext = get_string("Plaintext: ");

    printf("ciphertext: ");

    for(int i = 0; i < strlen(plaintext); i++)
    {
        if(isalpha(plaintext[i])){

            for(int j = 0; j < strlen(basic); j++)
            {
                if(tolower(plaintext[i]) == basic[j])
                {
                    if(isupper(plaintext[i]))
                    {
                        printf("%c", toupper(key[j]));
                    }
                    else
                    {
                        printf("%c", tolower(key[j]));
                    }
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }

    }

    printf("\n");



}