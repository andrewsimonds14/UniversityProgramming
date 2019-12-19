# Author: Andrew Simonds
# Student Number: 20056566
#
# I certify that this submission contains my own work, except as noted.”

from itertools import combinations
import random
import math


def BruteForce(inputSet, val):
    count = 0
    for length in range(len(inputSet) + 1):  # Iterate through all subset sizes
        for subset in combinations(inputSet, length):  # Combinations returns subsets of 'mainSet' of size length
            count += 1
            if sum(subset) == val:
                return count  # Solution found
    # print("No solution found for the target value")
    return count  # No solution found


def ModifiedBruteForce(inputSet):  # Similar to Brute Force, but returns list of subsets and list of sums of those
    # subsets
    count = 0
    subsetList = []
    subsetSums = []
    for length in range(len(inputSet) + 1):  # Iterate through all subset sizes
        for subset in combinations(inputSet, length):  # Combinations returns subsets of 'mainSet' of size length
            count += 1
            subsetList.append(subset)
            subsetSums.append(sum(subset))

    return subsetList, subsetSums, count


def SplitSet(inputSet):  # Splits inputSet into two equally long sets
    half = int(len(inputSet) / 2)
    return inputSet[:half], inputSet[half:]


def PairSums(values1, values2, val):  # Algorithm to find a pair of sums which add to the target value
    count = 0
    # Values1 and Values2 are sorted
    index1 = 0
    index2 = len(values2) - 1
    while index1 < len(values1) and (index2 >= 0):  # While neither set of sums has been iterated through fully
        x = values1[index1] + values2[index2]  # Sum to be checked
        if x == val:
            return index1, index2, count  # Value matches current sum, return indexes
        elif x < val:
            index1 += 1  # Test sum too small, move to next largest sum in values1
        else:
            index2 -= 1  # Test sum too large, move to next smallest sum in values2
    return -1, -1, count  # No matching sum found


def HorowitzSahni(inputSet, val):
    count = 0
    left, right = SplitSet(inputSet)
    leftSubsets, leftSums, leftCount = ModifiedBruteForce(left)
    count += leftCount
    rightSubsets, rightSums, rightCount = ModifiedBruteForce(right)
    count += rightCount
    for i in range(len(rightSubsets)):  # Check right subset sums for target value
        if rightSums[i] == val:
            return count
    for i in range(len(leftSubsets)):  # Check left subset sums for target value
        if leftSums[i] == val:
            return count
    # If the target value is not found in the above for loops, continue..
    leftSums.sort()
    count += 3 * len(inputSet) * (math.log2(len(inputSet)))  # Sorting take O(3nlogn) time
    rightSums.sort()
    count += 3 * len(inputSet) * (math.log2(len(inputSet)))  # Sorting take O(3nlogn) time
    successLeft, successRight, pairCount = PairSums(leftSums, rightSums, val)  # Store desired indexes in success variables
    count += pairCount
    if successLeft >= 0 and successRight >= 0:  # If no solution is found, success variables will be -1
        return count
    else:
        return count


# Driver for above functions
# Empty sets for keeping track of average counts
averageBFOperationsSet = []
averageHSOperationsSet = []
averageBFOperations = []
averageHSOperations = []
for setSize in range(4, 15):  # Set sizes
    for testNumber in range(1, 20):  # Number of tests
        bruteForceOperations = 0
        horowitzSahniOperations = 0
        testSet = random.sample(range(1, 100), setSize)  # Generate random set of integers
        targetValues = random.sample(range(1, 1000), 10)  # Generate random list of target values
        for z in range(len(targetValues)):
            bruteForceOperations += BruteForce(testSet, targetValues[z])  # Count operations
            horowitzSahniOperations += HorowitzSahni(testSet, targetValues[z])  # Count operations
        averageBFOperationsSet.append(bruteForceOperations // len(targetValues))  # Average operations per set
        averageHSOperationsSet.append(horowitzSahniOperations // len(targetValues))  # Average operations per set
    averageBFOperations.append(sum(averageBFOperationsSet) // 20)  # Overall average operations for BF Algorithm
    averageHSOperations.append(sum(averageHSOperationsSet) // 20)  # Overall average operations for HS Algorithm

file = open("testResults_Part2.txt", "w+")
file.write("{: <10} {: <20} {: <15} (measured by counts)\n".format("Set Size", "Brute Force Runtime", "Horowitz-Shani Runtime"))
for y in range(len(averageBFOperations)):
    file.write("{: <10} {: <20} {: <15}\n".format((y + 4), averageBFOperations[y], int(averageHSOperations[y])))
file.close()
