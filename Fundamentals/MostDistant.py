#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(coordinates):
    X = [x for x, y in coordinates if x]
    Y = [y for x, y in coordinates if y]

    x_dist = max(X) - min(X)
    y_dist = max(Y) - min(Y)
    xy_dist = (max(abs(x) for x in X)**2 + max(abs(y) for y in Y)**2)**0.5

    return (max(x_dist, y_dist, xy_dist))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    coordinates = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]

    result = solve(coordinates)

    fptr.write(str(result) + '\n')

    fptr.close()
