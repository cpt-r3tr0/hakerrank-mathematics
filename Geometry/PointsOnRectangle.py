#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(coordinates):
    xmax = -float("inf")
    xmin = float("inf")
    ymax = -float("inf")
    ymin = float("inf")

    # Get boundaries
    for i in coordinates:
        xmax = max(xmax,i[0])
        xmin = min(xmin,i[0])
        ymax = max(ymax,i[1])
        ymin = min(ymin,i[1])

    for i in coordinates:
        if i[0] < xmin or i[0] > xmax or i[1] < ymin or i[1] > ymax:
            return "NO"

        if not (i[0] == xmin or i[0] == xmax or i[1] == ymin or i[1] == ymax):
            return "NO"

    return "YES"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        n = int(input())

        coordinates = []

        for _ in range(n):
            coordinates.append(list(map(int, input().rstrip().split())))

        result = solve(coordinates)

        fptr.write(result + '\n')

    fptr.close()
