#!/bin/python3

import os
import sys
import math

# Complete the solve function below.
def solve(n, k):
    l = n*n/4 - n*k
    if l <0:
        return n-1
    min_x = (n/2)-math.sqrt(l)
    l_int_count = math.floor(min_x)
    ans = 2*l_int_count
    if ans == n:
        ans = n-1
    return ans


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        nk = input().split()

        n = int(nk[0])

        k = int(nk[1])

        result = solve(n, k)

        fptr.write(str(result) + '\n')

    fptr.close()
