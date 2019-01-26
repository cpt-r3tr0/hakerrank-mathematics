#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(a, b, d):
    if (d==0):
        return 0
    elif ((a==d) or (b==d)):
        return 1
    else:
        if (d%b):
            return max(2, d//b + 1)
        else:
            return (d//b)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        abd = input().split()

        a = int(abd[0])

        b = int(abd[1])

        d = int(abd[2])

        result = solve(a, b, d)

        fptr.write(str(result) + '\n')

    fptr.close()
