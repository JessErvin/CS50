#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int shift(char c);

int main(int argc, string argv[])
{
    // Check to make sure only 1 argument is entered
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            //Check to makesure the argument is a word
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    // Request plain text from the user
    string plain_text = get_string("plaintext: ");
    printf("ciphertext: ");
    // set counter for key
    int COUNT = 0;
    // convert the plain text to cipher text
    for (int i = 0; i < strlen(plain_text); i++)
    {
        // Set the key
        int key = shift(argv[1][COUNT % strlen(argv[1])]);

        // convert lower case letters & print
        if (islower(plain_text[i]))
        {
            printf("%c", ((plain_text[i] - 97 + (key % 26)) % 26) + 97);
            COUNT++;
        }
        // convert upper case letters & print
        else if (isupper(plain_text[i]))
        {
            printf("%c", ((plain_text[i] - 65 + (key % 26)) % 26) + 65);
            COUNT++;
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


int shift(char c)
{
    c = tolower(c);
    // Get the numeric value with a starting at 0
    int value = c - 97;
    return value;
}
