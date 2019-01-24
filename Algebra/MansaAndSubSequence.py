#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(s):
    n=len(s)
    s=s[::-1]
    m=10**9+7
    sum=0
    for i in range(n-1,-1,-1):
        sum+=(pow(11,i,m)*pow(2,(n-1-i),m)*int(s[i]))
    return sum%(m)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = solve(s)

    fptr.write(str(result) + '\n')

    fptr.close()
