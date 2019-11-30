# Uses the Caesar Cipher to encode messages

import sys
from cs50 import get_string


# Check the number of arguments
if len(sys.argv) == 2:
    # Check that the argument is a number
    if sys.argv[1].isnumeric:
        # store that argument as integer
        k = int(sys.argv[1])
    # Error message if arguments used incorrectly
    else:
        sys.exit("Usage: python caesar.py k")
else:
    sys.exit("Usage: python caesar.py k")


# Get input for the text to encode
plainText = get_string("plaintext: ")

# Set up the space for the cipher text (don't end the line)
print("ciphertext: ", end='')

# Iterate through the plaintext
for c in plainText:
    # Convert lowercase letters
    if c.islower():
        print(chr((ord(c) - 97 + k) % 26 + 97), end='')
    # Convert uppercase letters
    elif c.isupper():
        print(chr((ord(c) - 65 + k) % 26 + 65), end='')
    # Print spaces and puncuation as is
    else:
        print(c, end='')

# Print a new line to be pretty
print()
