#!/bin/python3

import os
import sys
from math import sqrt

# Complete the solve function below.
def solve(d, p):
    if d < 0:
        return 0
    ret = set()
    D1 = d * d + 4 * p
    if D1 >= 0:
        a = round((d - sqrt(D1)) / 2)
        if a * (d - a) == -p:
            ret.add((a, d - a))
        a = round((d + sqrt(D1)) / 2)
        if a * (d - a) == -p:
            ret.add((a, d - a))
        a = round((-d - sqrt(D1)) / 2)
        if a * (-d - a) == -p:
            ret.add((a, -d - a))
        a = round((-d + sqrt(D1)) / 2)
        if a * (-d - a) == -p:
            ret.add((a, -d - a))
    return len(ret)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        dp = input().split()

        d = int(dp[0])

        p = int(dp[1])

        result = solve(d, p)

        fptr.write(str(result) + '\n')

    fptr.close()
