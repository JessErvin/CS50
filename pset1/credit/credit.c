#include <cs50.h>
#include <stdio.h>
#include <math.h>

long get_cc(string prompt);
int get_digit_count(long cc_number);
string validation(long cc_number, int digits);
int luhns_algorithm(long cc_number);

int main(void)
{
    // Ask for our CC number
    long cc_number = get_cc("Number: ");
    int digits = get_digit_count(cc_number);
    string validation_check = validation(cc_number, digits);
    int luhns = luhns_algorithm(cc_number);
    // Print the Validation
    printf("%s\n", validation_check);
}

// Function that asks for a CC Number
long get_cc(string prompt)
{
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n <= 0);
    return n;
}

// Get the length of the CC Number
int get_digit_count(long cc_number)
{
    // Setting up our variables, total # of digits and a validation number we can iterate through 
    int total_digits = 0;
    long digit_validation = cc_number;
    
    while (digit_validation > 0)
    {
        digit_validation = digit_validation / 10;
        total_digits++;
    }
    return total_digits;
}

// Luhn's Algorithm
int luhns_algorithm(long cc_number)
{
    // Multiply every other digit by 2, starting with the number’s second-to-last digit.
    int digit1 = ((cc_number / 10) % 10) * 2;
    int digit2 = ((cc_number / 1000) % 10) * 2;
    int digit3 = ((cc_number / 100000) % 10) * 2;
    int digit4 = ((cc_number / 10000000) % 10) * 2;
    int digit5 = ((cc_number / 1000000000) % 10) * 2;
    int digit6 = ((cc_number / 100000000000) % 10) * 2;
    int digit7 = ((cc_number / 10000000000000) % 10) * 2;
    int digit8 = ((cc_number / 1000000000000000) % 10) * 2;
    
    // Add those products’ -digits- together.
    digit1 = digit1 % 10 + digit1 / 10;
    digit2 = digit2 % 10 + digit2 / 10;
    digit3 = digit3 % 10 + digit3 / 10;
    digit4 = digit4 % 10 + digit4 / 10;
    digit5 = digit5 % 10 + digit5 / 10;
    digit6 = digit6 % 10 + digit6 / 10;
    digit7 = digit7 % 10 + digit7 / 10;
    digit8 = digit8 % 10 + digit8 / 10;
    
    int check = digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8;
    
    //Add the sum to the sum of the digits that weren’t multiplied by 2.
    int digit9 = cc_number % 10;
    int digit10 = (cc_number / 100) % 10;
    int digit11 = (cc_number / 10000) % 10;
    int digit12 = (cc_number / 1000000) % 10;
    int digit13 = (cc_number / 100000000) % 10;
    int digit14 = (cc_number / 10000000000) % 10;
    int digit15 = (cc_number / 1000000000000) % 10;
    int digit16 = (cc_number / 100000000000000) % 10;
    
    // Add those products’ -digits- together.
    digit9 = digit9 % 10 + digit9 / 10;
    digit10 = digit10 % 10 + digit10 / 10;
    digit11 = digit11 % 10 + digit11 / 10;
    digit12 = digit12 % 10 + digit12 / 10;
    digit13 = digit13 % 10 + digit13 / 10;
    digit14 = digit14 % 10 + digit14 / 10;
    digit15 = digit15 % 10 + digit15 / 10;
    digit16 = digit16 % 10 + digit16 / 10;
    
    check = check + digit9 + digit10 + digit11 + digit12 + digit13 + digit14 + digit15 + digit16;
    
    return check;
}

// Check Card Validity
string validation(long cc_number, int digits)
{
    // Return Invalid if the number of digits is not 13, 16, or 15
    if (digits != 13 && digits != 16 && digits != 15)
    {
        return "INVALID";
    }
    else if (luhns_algorithm(cc_number) % 10 != 0)
    {
        return "INVALID";
    }
    // AMEX VALIDATION
    else if (digits == 15 && (cc_number / 10000000000000 == 34 || cc_number / 10000000000000 == 37))
    {
        return "AMEX";
    }
    // MASTERCARD VALIDATION
    else if (digits == 16 && (cc_number / 100000000000000 == 51 || 
                              cc_number / 100000000000000 == 52 || 
                              cc_number / 100000000000000 == 53 || 
                              cc_number / 100000000000000 == 54 || 
                              cc_number / 100000000000000 == 55))
    {
        return "MASTERCARD";
    }
    // VISA VALIDATION
    else if (digits == 16 && cc_number / 1000000000000000 == 4)
    {
        return "VISA";
    }
    else if (digits == 13 && cc_number / 1000000000000000 == 4)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}
