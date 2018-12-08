#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(a, b, k, m):
    x, y = a, b
    ansx, ansy = 1, 0
    while k>0:
        if k&1:
            ansx, ansy = (ansx*x - y*ansy)%m, (ansx*y + x*ansy)%m
        x, y = (x*x - y*y)%m, (2*x*y)%m
        k >>= 1
    return (ansx, ansy)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        abkm = input().split()

        a = int(abkm[0])

        b = int(abkm[1])

        k = int(abkm[2])

        m = int(abkm[3])

        result = solve(a, b, k, m)

        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')

    fptr.close()
