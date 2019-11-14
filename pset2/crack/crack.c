#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

// set the total # of letters availible for use in passwords
const int TOTAL_LETTERS = 52;
const char ALPHABET[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // Check to make sure only 1 argument is entered
    if (argc == 2)
    {
        // Set the hash
        string hash = argv[1];
        // Set the salt
        char salt[3];
        salt[0] = hash[0];
        salt[1] = hash[1];
        salt[2] = '\0';
        
        // Set up a password with no more than 1 letter
        char password1[2];
        
        // iterate through 1 character passwords
        for (int i =0; i < TOTAL_LETTERS; i++)
        {
            password1[0] = ALPHABET[i];
            password1[1] = '\0';
            if (strcmp(crypt(password1, salt), hash) == 0)
            {
                printf("%s\n", password1);
                return 0;
            }
        }
        
        // Set up a password with no more than 2 letters
        char password2[3];
        // iterate through 2 character passwords    
        for (int i = 0; i < TOTAL_LETTERS; i++)
        {
            for (int j = 0; j < TOTAL_LETTERS; j++)
            {
                password2[0] = ALPHABET[i];
                password2[1] = ALPHABET[j];
                password2[2] = '\0';
                if (strcmp(crypt(password2, salt), hash) == 0)
                {
                    printf("%s\n", password2);
                    return 0;
                }
            }
        }
        // Set up a password with no more than 3 letters
        char password3[4];
        for (int i = 0; i < TOTAL_LETTERS; i++)
        {
            for (int j = 0; j < TOTAL_LETTERS; j++)
            {
                for (int k = 0; k < TOTAL_LETTERS; k++)
                {
                    password3[0] = ALPHABET[i];
                    password3[1] = ALPHABET[j];
                    password3[2] = ALPHABET[k];
                    password3[3] = '\0';
                    if (strcmp(crypt(password3, salt), hash) == 0)
                    {
                        printf("%s\n", password3);
                        return 0;
                    }
                }
            }
        }
        // Set up a password with no more than 4 letters
        char password4[5];
        for (int i = 0; i < TOTAL_LETTERS; i++)
        {
            for (int j = 0; j < TOTAL_LETTERS; j++)
            {
                for (int k = 0; k < TOTAL_LETTERS; k++)
                {
                    for (int l = 0; l < TOTAL_LETTERS; l++)
                    {
                        password4[0] = ALPHABET[i];
                        password4[1] = ALPHABET[j];
                        password4[2] = ALPHABET[k];
                        password4[3] = ALPHABET[l];
                        password4[4] = '\0';
                        if (strcmp(crypt(password4, salt), hash) == 0)
                        {
                            printf("%s\n", password4);
                            return 0;
                        }
                    }
                }
            }
        }
        // Set up a password with no more than 5 letters
        char password5[6];
        for (int i = 0; i < TOTAL_LETTERS; i++)
        {
            for (int j = 0; j < TOTAL_LETTERS; j++)
            {
                for (int k = 0; k < TOTAL_LETTERS; k++)
                {
                    for (int l = 0; l < TOTAL_LETTERS; l++)
                    {
                        for (int m = 0; m < TOTAL_LETTERS; m++)
                        {
                            password5[0] = ALPHABET[i];
                            password5[1] = ALPHABET[j];
                            password5[2] = ALPHABET[k];
                            password5[3] = ALPHABET[l];
                            password5[4] = ALPHABET[m];
                            password5[5] = '\0';
                            if (strcmp(crypt(password5, salt), hash) == 0)
                            {
                                printf("%s\n", password5);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        printf("I couldn't guess the password\n");
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
}
