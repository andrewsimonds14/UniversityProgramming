# Author: Andrew Simonds
# Student Number: 20056566
#
# I certify that this submission contains my own work, except as noted.”

import math
import numpy as np
import time

# Import text file as array (*****Path must be changed if testing on different computer*****)
with open('C:/Users/andre/PycharmProjects/ConnectingFlights/' + str(input('File name: '))) as textFile:
    graph = [line.split() for line in textFile]

# Array format: a[x][0] = Starting City, a[x][1] = Destination City, a[x][2] = Departure Time, a[x][3] = Arrival Time

# Get number of cities and flight possibilities
numCities = int(graph[0][0])
numFlights = len(graph) - 1

# Get input for start and destination city
startCity = int(input("Starting City: "))
destCity = int(input("Destination City: "))

# Remove first line and convert strings to integers
graph = ([list(map(int, i)) for i in graph])
graph = np.delete(graph, 0, None)

# Initialize variable to check if algorithm is done and set city variable to start destination
finished = False
city = startCity

# Initialize reached array
for i in range(numCities):
    reached.append(False)

# Initialize other arrays to the same length to keep track of estimates, candidates, costs, and predecessors
reached[startCity] = True
estimate = [math.inf] * len(reached)
candidate = [False] * len(reached)
cost = [0] * len(reached)
predecessor = [-1] * len(reached)

# Obtain initial neighbours of startCity, if we're at startCity, and the estimate for the destination is less than
# current estimate
for i in range(numFlights):
    if (graph[i][0] == city) & (estimate[graph[i][1]] > graph[i][3]):
        estimate[graph[i][1]] = graph[i][3]
        candidate[graph[i][1]] = True
        predecessor[graph[i][1]] = city

# Set initial cost of flight to 0
cost[startCity] = 0

# Find the best candidate using Dijkstra's Algorithm
while not finished:

    # Initialize best candidate
    best_candidate_estimate = math.inf

    # Loop to determine which path should be explored next, if the next city is a candidate, and if its estimate is
    # less than the current estimate for that city
    for i in range(numFlights):
        if candidate[graph[i][1]] & (estimate[graph[i][1]] < best_candidate_estimate):
            city = graph[i][1]
            best_candidate_estimate = estimate[graph[i][1]]

    # Update current city in the arrays
    cost[city] = int(estimate[city])
    reached[city] = True
    candidate[city] = False

    # Update neighbours of current city
    for i in range(numFlights):

        # If we're on the current city, and the destination city hasn't been reached
        if (graph[i][0] == city) & (reached[graph[i][1]] == False):
            # print("TEST 1")

            # If the arrival time of the flight is less than the current estimate for the destination city
            if graph[i][3] < estimate[graph[i][1]]:
                # print("TEST 2")

                # If the cost of the current city is less than the departure time of the flight
                if cost[city] < graph[i][2]:
                    # print("TEST 3")

                    # Update neighbours of current city
                    estimate[graph[i][1]] = graph[i][3]
                    candidate[graph[i][1]] = True
                    predecessor[graph[i][1]] = city

    # If there is no flight to be had
    if startCity == destCity:
        print("No need to fly silly, go home")
        break

    # If we've reached the destination city
    if city == destCity:
        finished = True

        # Initialize path array with destination city
        path = [destCity]
        x = destCity

        # Fill path array with predecessors in reverse order
        while x != startCity:
            time.sleep(1)
            path.append(predecessor[x])
            x = predecessor[x]

        # Reverse path to proper order
        path.reverse()

        # Print results
        print("\n\nOptimal route from", startCity, "to", destCity, '...\n')
        for i in range(len(path) - 1):
            print("Fly from", path[i], "to", path[i + 1], "... Arriving at", cost[path[i + 1]])
        print("\nArrival time at city", destCity, "->", cost[city])
    else:
        finished = False

# 2019_Lab_2_flights_test_data.txt
# 2019_Lab_2_flights_real_data.txt
