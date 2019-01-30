#!/bin/python3

import os
import sys
from math import sin,cos,pi

# Complete the solve function below.
def solve(n):
    cosplus=[1,cos(1/2)];cosminus=[1,cos(1/2)]
    for i in range(2,n+1):
        x=cos(i/2-1)
        if x>cosplus[-2]:
            cosplus+=[x]
        else:
            cosplus+=[cosplus[-2]]
        if x<cosminus[-2]:
            cosminus+=[x]
        else:
            cosminus+=[cosminus[-2]]
    sol=[max(2*sin(k/2)*cosplus[k],2*sin(k/2)*cosminus[k]) for k in range(n+1)]

    return(max(sin(i)+sol[n-i] for i in range(1,n-1)))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    result = solve(n)

    fptr.write(str(result) + '\n')

    fptr.close()
