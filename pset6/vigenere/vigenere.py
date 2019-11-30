# Uses the Vigenere Cipher to encode messages

import sys
from cs50 import get_string


# Check the number of arguments
if len(sys.argv) == 2:
    # Check that the argument is a number
    if sys.argv[1].isalpha():
        # store that argument as integer
        k = sys.argv[1].lower()
    # Error message if arguments used incorrectly
    else:
        sys.exit("Usage: python vigenere.py k")
else:
    sys.exit("Usage: python vigenere.py k")


# Get input for the text to encode
plainText = get_string("plaintext: ")

# Set up the space for the cipher text (don't end the line)
print("ciphertext: ", end='')

# Initialize a counter for k
count = 0

# Iterate through the plaintext
for c in plainText:

    key = ord(k[count % len(k)]) - 97
    # Convert lowercase letters
    if c.islower():
        print(chr((ord(c) - 97 + key) % 26 + 97), end='')
        count += 1
    # Convert uppercase letters
    elif c.isupper():
        print(chr((ord(c) - 65 + key) % 26 + 65), end='')
        count += 1
    # Print spaces and puncuation as is
    else:
        print(c, end='')

# Print a new line to be pretty
print()
