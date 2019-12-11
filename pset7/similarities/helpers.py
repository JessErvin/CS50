from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Create lists of lines
    aList = a.splitlines()
    bList = b.splitlines()
    finalList = []

    # Compare Lists
    for line in aList:
        if line in bList:
            finalList.append(line)
    return list(set(finalList))


def sentences(a, b):
    """Return sentences in both a and b"""

    # Create lists of sentences
    aList = sent_tokenize(a)
    bList = sent_tokenize(b)
    finalList = []

    # Compare Lists
    for sentence in aList:
        if sentence in bList:
            finalList.append(sentence)

    return list(set(finalList))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    aList = []
    bList = []
    finalList = []

    # create lists of substrings
    for i in range(0, (len(a) - n + 1)):
        aList.append(a[i:(i + n)])
    for j in range(0, (len(b) - n + 1)):
        bList.append(b[j:(j + n)])

    # Compare the two lists
    for subString in aList:
        if subString in bList:
            finalList.append(subString)

    return list(set(finalList))
