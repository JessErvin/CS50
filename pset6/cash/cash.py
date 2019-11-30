# Get the smallest number of coins you can give back as change

from cs50 import get_float

# Wait for a positive float
while True:
    totalChange = get_float("Change owed: ")
    if totalChange > 0:
        break

# Initialize cents and start counting
cents = int(round(totalChange * 100))

# Quarters First!
totalCoins = cents // 25
cents = cents % 25

# Dimes are next
totalCoins += cents // 10
cents = cents % 10

# Nickles are next
totalCoins += cents // 5
cents = cents % 5

# Pennies are last!
totalCoins += cents

print(totalCoins)