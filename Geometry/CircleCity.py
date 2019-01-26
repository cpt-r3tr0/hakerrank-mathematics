#!/bin/python3

import os
import sys
import math

# Complete the solve function below.
def solve(d, k):
    s = 0;
    for i in range(0,math.ceil(d**0.5)):
        j = math.ceil((d - i*i)**0.5)
        if i*i+j*j==d:
            s=s+4
    if k>=s:
        return "possible"
    else:
        return "impossible"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        dk = input().split()

        d = int(dk[0])

        k = int(dk[1])

        result = solve(d, k)

        fptr.write(result + '\n')

    fptr.close()
