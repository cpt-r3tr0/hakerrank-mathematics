#!/bin/python3

import os
import sys

def dotProd (v1, v2):
    rst = 0
    for i in range(3):
        rst += v1[i] * v2[i]
    return rst

# Complete the solve function below.
def solve(r1, r2, position1, position2, acceleration1, acceleration2):
    delA = [acceleration1[i] - acceleration2[i] for i in range(3)]
    delP = [position1[i] - position2[i] for i in range(3)]

    # t is the value after solving dx/dt = 0
    t = -dotProd(delA, delP)/dotProd(delA, delA)
    if t <= 0:
        return 'NO'

    difDist = dotProd(delP, delP) - dotProd(delA, delP)**2/dotProd(delA, delA) - (r1 + r2)**2
    if difDist > 0:
        return 'NO'
    else:
        return 'YES'

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        r1R2 = input().split()

        r1 = int(r1R2[0])

        r2 = int(r1R2[1])

        position1 = list(map(int, input().rstrip().split()))
        acceleration1 = list(map(int, input().rstrip().split()))

        position2 = list(map(int, input().rstrip().split()))
        acceleration2 = list(map(int, input().rstrip().split()))

        result = solve(r1, r2, position1, position2, acceleration1, acceleration2)

        fptr.write(result + '\n')

    fptr.close()
