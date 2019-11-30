# A program that decrypts passwords

import sys
import crypt


# Check the number of arguments
if len(sys.argv) == 2:
    # Save the hash as h
    h = sys.argv[1]
else:
    sys.exit("Usage: python crack.py hash")

# Set up our alphabet
ALPHABET = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

# Iterate through all possible combinations
for letterFive in ALPHABET:
    for letterFour in ALPHABET:
        for letterThree in ALPHABET:
            for letterTwo in ALPHABET:
                for letterOne in ALPHABET:
                    # Remove any spaces from the password
                    password = f"{letterOne}{letterTwo}{letterThree}{letterFour}{letterFive}".strip()

                    # Hash the password and compare the result to the argv
                    if h == crypt.crypt(password, h[:2]):
                        print(password)
                        sys.exit()