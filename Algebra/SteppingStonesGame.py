#!/bin/python3

import os
import sys
from math import sqrt

# Complete the solve function below.
def solve(n):
    j=(1+sqrt(1+8*n))/2
    if abs(j-int(j))<=0:
        return("Go On Bob " + str(int(j-1)))
    else:
        return("Better Luck Next Time")

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        result = solve(n)

        fptr.write(result + '\n')

    fptr.close()
