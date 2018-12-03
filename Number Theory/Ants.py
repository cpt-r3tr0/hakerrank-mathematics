#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(V, N):
    C = [1]
    for i in range(1,N):
        if V[i]-V[i-1]==1:
            C[-1] += 1
        else:
            C.append(1)
    if V[0]+1000-V[N-1]==1:
        C[0] += C.pop()
    a = N//2
    b = N-a
    res = 400000*a*b
    for c in C:
        res += 2*(c//2)
    return (res)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    V_count = int(input())

    V = sorted(map(int, input().rstrip().split()))

    result = solve(V,V_count)

    fptr.write(str(result) + '\n')

    fptr.close()
