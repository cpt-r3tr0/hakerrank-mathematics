#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(n):
    if n==1 or n==2:
        return -1
    elif n%2==1:
        return 2
    elif n%4==0:
        return 3
    else:
        return 4

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        result = solve(n)

        fptr.write(str(result) + '\n')

    fptr.close()
