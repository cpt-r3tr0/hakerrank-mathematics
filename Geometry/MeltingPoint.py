#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(coordinates):
    l=sorted(x[0]+x[1] for x in coordinates)
    ll=sorted(x[1]-x[0] for x in coordinates)
    n=len(l)
    d=[sum(x-l[0] for x in l)]
    w={l[0]:d[0]}
    for i in range(1,n):
        d+=[d[-1]+(l[i]-l[i-1])*(-n+2*i)]
        w[l[i]]=d[-1]
    d=[sum(x-ll[0] for x in ll)]
    w2={ll[0]:d[0]}
    for i in range(1,n):
        d+=[d[-1]+(ll[i]-ll[i-1])*(-n+2*i)]
        w2[ll[i]]=d[-1]
    return(min(w[x[0]+x[1]]+w2[x[1]-x[0]] for x in coordinates)//2)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    coordinates = []

    for _ in range(n):
        coordinates.append(list(map(int, input().rstrip().split())))

    result = solve(coordinates)

    fptr.write(str(result) + '\n')

    fptr.close()
