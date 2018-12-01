#!/bin/python3

import os
import sys
from array import array
from bisect import bisect_left


# Complete the solve function below.
def solve(n):
    d = {}
    for i in range(1, n):
        for j in range(1, n//i + 1):
            if not i*j in d:
                d[i*j] = array('l')
            d[i*j].append(i)
    pairs = {}
    for p in range(1, n):
        for a in d[p]:
            if not a in pairs:
                pairs[a] = array('l')
            pairs[a].extend(d[n-p][:bisect_left(d[n-p], a)])

    return (sum(len(set(v)) for i, v in pairs.items()))


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    result = solve(n)

    fptr.write(str(result) + '\n')

    fptr.close()
