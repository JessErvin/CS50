from cs50 import get_int

# Wait for a valid input
while True:
    cc = get_int("Number: ")
    if cc > 0:
        break

ccNum = str(cc)

# Make a function for Luhns Algorithm


def luhns(ccNum):
    check = 0
    ccReverse = ccNum[::-1]

    # Multiply every other digit by 2, starting with the number’s second-to-last digit.
    for i in range(len(ccReverse)):
        if i % 2 == 0:
            check += int(ccReverse[i])

        # Add the sum to the sum of the digits that weren’t multiplied by 2.
        else:
            temp = int(ccReverse[i]) * 2

            # Add those products’ -digits- together.
            check += temp % 10 + temp // 10

    return check


def validation(ccNum):
    # Count the number of digits
    totalDigits = len(ccNum)

    # Return Invalid if the number of digits is not 13, 16, or 15
    if totalDigits != 13 and totalDigits != 15 and totalDigits != 16:
        print("INVALID")

    # Return invalid if the card does not pass Luhns Algorithm
    elif luhns(ccNum) % 10 != 0:
        print("INVALID")

    # AMEX Validation:
    elif totalDigits == 15 and (int(ccNum[0:2]) == 34 or int(ccNum[0:2]) == 37):
        print("AMEX")

    # MASTERCARD Validation
    elif totalDigits == 16 and (int(ccNum[0:2]) == 51 or
                                int(ccNum[0:2]) == 52 or
                                int(ccNum[0:2]) == 53 or
                                int(ccNum[0:2]) == 54 or
                                int(ccNum[0:2]) == 55):
        print("MASTERCARD")

    # VISA Validation
    elif (totalDigits == 16 or totalDigits == 13) and int(ccNum[0]) == 4:
        print("VISA")

    # Assume any other input is invalid
    else:
        print("INVALID")


validation(ccNum)
