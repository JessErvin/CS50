# A program that censors messages that contain words on a list of supplied 'banned words'

from cs50 import get_string
import sys


def main():

    # Check for correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")

    # Ask the user for the message and store
    message = get_string("What message would you like to censor? ")

    # Create a list of the banned words
    bannedWords = open(sys.argv[1]).readlines()
    bannedWords = [i.replace('\n', '') for i in bannedWords]

    # check the words agains the list
    for word in message.split():
        if word.lower() in bannedWords:
            for c in word:
                print("*", end="")
        else:
            print(word, end="")
        print(" ", end="")
    print()


if __name__ == "__main__":
    main()
