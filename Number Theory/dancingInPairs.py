#!/bin/python3

import os
import sys
from math import floor, sqrt

# Complete the solve function below.
def solve(i):
    k = floor(sqrt(i))
    if k*k > i:
        k = k-1
    if (k % 2):
        return ("odd")
    else:
        return ("even")

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        i = int(input())

        result = solve(i)

        fptr.write(result + '\n')

    fptr.close()
