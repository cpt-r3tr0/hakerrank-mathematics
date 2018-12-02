#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(a, b):
    base = 2
    for _ in range(a):
        base = (base * base) % b
    return base

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    ab = input().split()

    a = int(ab[0])

    b = int(ab[1])

    result = solve(a, b)

    fptr.write(str(result) + '\n')

    fptr.close()
