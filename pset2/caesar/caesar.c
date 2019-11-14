#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check to make sure only one argument was entered
    if (argc == 2)
    {
        //Check to make sure the argument is an int
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // store argv as an int 'k'
    int k = atoi(argv[1]);
    
    // get user input for plain text
    string plain_text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // convert the plain text to cipher text
    for (int i = 0; i < strlen(plain_text); i++)
    {
        // convert lower case letters & print
        if (islower(plain_text[i]))
        {
            printf("%c", ((plain_text[i] - 97 + (k % 26)) % 26) + 97);
        }
        // convert upper case letters & print
        else if (isupper(plain_text[i]))
        {
            printf("%c", ((plain_text[i] - 65 + (k % 26)) % 26) + 65);
        }
        // print punctuation & spaces as is
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    return 0;
}
