#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(a):
    n = len(a)
    ones = a.count(1)
    twos = a.count(2)
    s = sum(a) - ones
    return ones * (ones - 1) // 2 * 2  + ones * (n - ones) + twos * (twos - 1) // 2


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        a_count = int(input())

        a = list(map(int, input().rstrip().split()))

        result = solve(a)

        fptr.write(str(result) + '\n')

    fptr.close()
