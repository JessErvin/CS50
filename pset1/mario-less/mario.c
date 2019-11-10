#include <cs50.h>
#include <stdio.h>

int get_number_of_bricks(string prompt);
int pyramid_build(int bricks);

int main(void)
{
    int bricks = get_number_of_bricks("Enter a Number between 1 & 8:\n");
    // This line was printing the stored number
    // printf("Stored: %d\n", bricks);
    pyramid_build(bricks);
}

// Prompt user for a number of bricks between 1 & 8
int get_number_of_bricks(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}

// Print your pyramid
int pyramid_build(int bricks)
{
    // Starts a new row in the pyramid
    for (int i = bricks - 1; i >= 0; i--)
    {
        // adds the spaces before your pyramid
        for (int k = i; k > 0; k--)
        {
            printf(" ");
        }
        // adds the pyramid bricks
        for (int j = i; j < bricks; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
