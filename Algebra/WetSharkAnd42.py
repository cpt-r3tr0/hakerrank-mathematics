#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(s):
    x = s * 2
    temp1 = x // 42
    x += (temp1) * 2
    temp2 = x // 42
    while (temp1 < temp2):
        x += (temp2 - temp1) * 2
        temp1 = temp2
        temp2 = x // 42
    return x % 1000000007

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        s = int(input())

        result = solve(s)

        fptr.write(str(result) + '\n')

    fptr.close()
