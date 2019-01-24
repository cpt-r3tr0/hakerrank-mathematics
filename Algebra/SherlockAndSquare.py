#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(n):
    ans=pow(2,n+1,1000000007)+2
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        result = solve(n)

        fptr.write(str(result) + '\n')

    fptr.close()
