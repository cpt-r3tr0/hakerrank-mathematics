#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(stars):
    if len(stars)==1:
        return(0)
    else:
        W=sum(x[2] for x in stars)
        wmax=0
        for i in range(len(stars)):
            for j in range(len(stars)):
                x1,y1=stars[i][:2]
                x2,y2=stars[j][:2]
                a,b,c=y1-y2,x2-x1,(y1-y2)*x1+(x2-x1)*y1
                w=sum(x[2] for x in stars if x[0]*a+x[1]*b<c)+stars[i][2]
                w=min(w,W-w)
                wmax=max(w,wmax)
        return(wmax)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    stars = []

    for _ in range(n):
        stars.append(list(map(int, input().rstrip().split())))

    result = solve(stars)

    fptr.write(str(result) + '\n')

    fptr.close()
