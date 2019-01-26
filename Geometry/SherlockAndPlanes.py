#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(points):
    a0 = list(set([x[0] for x in points]))
    a1 = list(set([x[1] for x in points]))
    a2 = list(set([x[2] for x in points]))
    if len(a0)==1 or len(a1)==1 or len(a2)==1:
        return 'YES'
    else:
        return 'NO'

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        points = []

        for _ in range(4):
            points.append(list(map(int, input().rstrip().split())))

        result = solve(points)

        fptr.write(result + '\n')

    fptr.close()
