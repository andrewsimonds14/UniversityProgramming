# Created on November 22, 2019
# Andrew Simonds - 20056566 - 16avs6

import sys


# Used method three from Lab 9 to change
def f2mod(s):
    result = 0
    for char in s:
        result = (7 * result + ord(char)) % 100000
    return result


# Returns length of LCS for X[0..m-1], Y[0..n-1]
def longestCommonSubsequence(X, Y, m, n):
    tableL = [[0 for x in range(n + 1)] for x in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 or j == 0:
                tableL[i][j] = 0
            # First check if not equal with function
            elif f2mod(X[i - 1]) != f2mod(Y[j - 1]):
                tableL[i][j] = max(tableL[i - 1][j], tableL[i][j - 1])
            # If they are equal from the function, check the actual strings
            else:
                if X[i - 1] == Y[j - 1]:
                    tableL[i][j] = tableL[i - 1][j - 1] + 1
                else:
                    tableL[i][j] = max(tableL[i - 1][j], tableL[i][j - 1])

    index = tableL[m][n]  # Bottom right corner of table

    lcs = [""] * (index + 1)
    lcs[index] = ""

    # Start iteration at bottom right corner
    i = m
    j = n

    while i > 0 and j > 0:
        # If current string in X and Y are the same then it must be apart of the longest common subsequence
        if X[i - 1] == Y[j - 1]:
            lcs[index - 1] = X[i - 1]
            # Decrement row, column, and index
            i -= 1
            j -= 1
            index -= 1
        # Find next largest value, being either above or beside, and move to that one
        elif tableL[i - 1][j] > tableL[i][j - 1]:
            i -= 1
        else:
            j -= 1

    print("LCS of is \n")
    lineCount = 0
    for x in range(len(lcs)):
        print(lcs[x])
        lineCount = lineCount + 1
    print(lineCount)
    print("'lcs' contains all lines that are equal in X and Y")
    print(lcs[64])
    return lcs


# file1 = "Three_Bears.v1.txt"
# file2 = "Three_Bears.v2.txt"

file1 = "Dijkstra.py"
file2 = "Dijkstra_py3.py"

with open(file1) as f:
    lineList1 = f.read().splitlines()

with open(file2) as f:
    lineList2 = f.read().splitlines()

lengthList1 = len(lineList1)
lengthList2 = len(lineList2)

commonLineList = longestCommonSubsequence(lineList1, lineList2, lengthList1, lengthList2)

# Keep track of where we are in the files
lineCount1 = 0
lineCount2 = 0
commonCount = 0

# Store line numbers where the common line is in each file
fileLine1 = []
fileLine2 = []

while lineCount1 < lengthList1 and lineCount2 < lengthList2:
    if lineList1[lineCount1] == commonLineList[commonCount]:
        fileLine1.append(lineCount1 + 1)
        while True:
            if lineList2[lineCount2] == commonLineList[commonCount]:
                fileLine2.append(lineCount2 + 1)
                commonCount = commonCount + 1
                lineCount2 = lineCount2 + 1
                break
            lineCount2 = lineCount2 + 1

    lineCount1 = lineCount1 + 1

print("Outputting arrays")

for x in range(len(fileLine1)):
    print(fileLine1[x])

for x in range(len(fileLine2)):
    print(fileLine2[x])

# Print final output
count1 = 0
count2 = 0

print(len(fileLine1))
print(len(fileLine2))

while count1 + 1 < len(fileLine1) and count2 + 1 < len(fileLine2):
    # Print sequence of matches
    print("Match: ", end=" ")
    print(file1, end=" ")

    temp1 = fileLine1[count1]
    tempCount = 0
    while ((fileLine1[count1 + 1] - fileLine1[count1]) == 1) and ((count1 + 2) < len(fileLine1)):
        count1 = count1 + 1
        tempCount = tempCount + 1

    if (count1 + 2) >= len(fileLine1):
        count1 = count1 + 1

    print("<{} .. {}>".format(temp1, fileLine1[count1]), end=" ")
    print(" ---> ", end=" ")
    print(file2, end=" ")

    temp2 = fileLine2[count2]
    tempCount = 0
    while (fileLine2[count2 + 1] - fileLine2[count2]) == 1 and (count2 + 2) < len(fileLine2) and tempCount < (
            fileLine1[count1] - temp1):
        count2 = count2 + 1
        tempCount = tempCount + 1

    if (count2 + 2) >= len(fileLine1):
        count2 = count2 + 1

    print("<{} .. {}>".format(temp2, fileLine2[count2]))

    if not ((count1 + 1) < len(fileLine1) and (count2 + 1) < len(fileLine2)):
        break

    # Print sequence of mismatches
    print("Mismatch: ", end=" ")
    print(file1, end=" ")
    if (fileLine1[count1 + 1] - fileLine1[count1]) == 1:
        print("None", end=" ")
    else:
        print("<{} .. {}>".format(fileLine1[count1] + 1, fileLine1[count1 + 1] - 1), end=" ")
    print(" ---> ", end=" ")
    print(file2, end=" ")
    if (fileLine2[count2 + 1] - fileLine2[count2]) == 1:
        print("None")
    else:
        print("<{} .. {}>".format(fileLine2[count2] + 1, fileLine2[count2 + 1] - 1))

    count1 = count1 + 1
    count2 = count2 + 1
