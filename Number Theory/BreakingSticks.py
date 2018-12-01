#!/bin/python3

import math
import os
import random
import re
import sys

def solve(x):
    os.system("factor {} > factors.txt".format(x))
    with open("factors.txt") as f:
        factors = [int(x) for x in f.read().split()[1:]]
        prod = 1
        ans = x
        for j in sorted(factors, reverse=True):
            ans += prod
            prod *= j
        return ans
# Complete the longestSequence function below.
def longestSequence(a):
    # Return the length of the longest possible sequence of moves.
    ans = 0
    for i in a:
        ans += solve(i)
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    a = list(map(int, input().rstrip().split()))

    result = longestSequence(a)

    fptr.write(str(result) + '\n')

    fptr.close()
