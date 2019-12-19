# Author: Andrew Simonds
# Student Number: 20056566
#
# I certify that this submission contains my own work, except as noted.”

from itertools import combinations


def BruteForce(inputSet, val):
    file.write("Brute Force Algorithm:\n")
    for length in range(len(inputSet) + 1):  # Iterate through all subset sizes
        for subset in combinations(inputSet, length):  # Combinations returns subsets of 'inputSet' of size 'length'
            if sum(subset) == val:
                file.write('Solution found -> {}\n'.format(subset))
                return
    file.write("No solution found for the target value\n")


def ModifiedBruteForce(inputSet):  # Similar to Brute Force, but returns list of subsets and list of sums of those
    subsetList = []
    subsetSums = []
    for length in range(len(inputSet) + 1):  # Iterate through all subset sizes
        for subset in combinations(inputSet, length):  # Combinations returns subsets of 'mainSet' of size length
            subsetList.append(subset)
            subsetSums.append(sum(subset))

    return subsetList, subsetSums


def SplitSet(inputSet):  # Splits inputSet into two equally long sets
    half = int(len(inputSet) / 2)
    return inputSet[:half], inputSet[half:]


def PairSums(values1, values2, val):  # Algorithm to find a pair of sums which add to the target value
    # Values1 and Values2 are sorted
    index1 = 0
    index2 = len(values2) - 1
    while index1 < len(values1) and (index2 >= 0):  # While neither set of sums has been iterated through fully
        x = values1[index1] + values2[index2]  # Sum to be checked
        if x == val:
            return index1, index2  # Value matches current sum, return indexes
        elif x < val:
            index1 += 1  # Test sum too small, move to next largest sum in values1
        else:
            index2 -= 1  # Test sum too large, move to next smallest sum in values2
    return -1, -1  # No matching sum found


def HorowitzSahni(inputSet, val):
    file.write("HorowitzSahni Algorithm:\n")
    left, right = SplitSet(inputSet)
    leftSubsets, leftSums = ModifiedBruteForce(left)
    rightSubsets, rightSums = ModifiedBruteForce(right)
    for i in range(len(rightSubsets)):  # Check right subset sums for target value
        if rightSums[i] == val:
            file.write('Solution found -> {}'.format(rightSubsets[i]))
            return
    for i in range(len(leftSubsets)):  # Check left subset sums for target value
        if leftSums[i] == val:
            file.write('Solution found -> {}'.format(leftSubsets[i]))
            return
    # If the target value is not found in the above for loops, continue..
    leftSums.sort()
    rightSums.sort()
    successLeft, successRight = PairSums(leftSums, rightSums, val)  # Store desired indexes in success variables
    if successLeft >= 0 and successRight >= 0:  # If no solution is found, success variables will be -1
        file.write('Solution found -> {} and {}'.format(leftSubsets[successLeft], rightSubsets[successRight]))
    else:
        file.write("No solution found for the target value")


# Driver for above functions
testSet = [10, 20, 30]
targetVal = int(input("Target Value (Can't be 0): "))

file = open("testEvidence_Part1.txt", "w+")
file.write("Test Set: ")
for z in range(len(testSet)):  # Print test set
    file.write("{}  ".format(testSet[z]))
file.write("\nExample Target Value: {}\n\n".format(targetVal))  # Print target value

BruteForce(testSet, targetVal)
HorowitzSahni(testSet, targetVal)

file.close()
