#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_change(string prompt);
int coin_count(float total_change);

int main(void)
{
    float total_change = get_change("Change Owed: ");
    // Print the amount owed
    printf("The amount owed is %.2f\n", total_change);
    int total_coins = coin_count(total_change);
    // Print the total number of coins needed
    printf("%d\n", total_coins);
}

// Prompt user for the amount of change owed
float get_change(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    while (n <= 0);
    return n;
}

int coin_count(float total_change)
{
    // turn the float into an int
    int cents = round(total_change * 100);
    int total_coins = 0;
    int remaining_cents = cents;
    
    // Count the Quarters
    for (int i = cents; i >= 25;)
    {
        int quarters = (i / 25);
        remaining_cents = i % 25;
        i = remaining_cents;
        total_coins += quarters;
    }
    // Count the Dimes
    for (int j = remaining_cents; j >= 10;)
    {
        int dimes = (j / 10);
        remaining_cents = j % 10;
        j = remaining_cents;
        total_coins += dimes;
    }        
    // Count the nickles
    for (int k = remaining_cents; k >= 5;)
    {
        int nickles = k / 5;
        remaining_cents = k % 5;
        k = remaining_cents;
        total_coins += nickles;
    }            
    // The remaining are pennies
    for (int l = remaining_cents; l >= 1;)
    {
        int pennies = l;
        remaining_cents = 0;
        l = remaining_cents;
        total_coins += pennies;
    }
    return total_coins;
}
