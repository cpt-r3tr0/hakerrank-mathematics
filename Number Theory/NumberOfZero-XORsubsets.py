#!/bin/python3

import os
import sys

mod = 10**9 + 7
# Complete the solve function below.
def solve(n):
    a = (pow(2, n, mod - 1) - n) % (mod - 1)
    return (pow(2, a, mod))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        result = solve(n)

        fptr.write(str(result) + '\n')

    fptr.close()
