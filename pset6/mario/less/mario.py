from cs50 import get_int

# Wait for a valid input
while True:
    bricks = get_int("Height: ")
    if bricks > 0 and bricks <= 8:
        break
# initialize i
i = 0


while i < bricks:
    # Initialize j and print spaces without a new line
    j = 0
    while j < (bricks - 1 - i):
        print(" ", end='')
        j += 1

    # Initialize k and print bricks without a new line
    k = 0
    while k <= i:
        print("#", end='')
        k += 1
    i += 1

    # Move on to the next line
    print()
