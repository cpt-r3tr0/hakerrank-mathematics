#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(n, k):
    a=[0]*k
    a[0]=n//k
    for i in range(1,n%k+1):
        a[i]=a[0]+1
    for i in range(n%k+1,k):
        a[i]=a[0]

    count=0
    count= (a[0]*(a[0]-1))//2
    loop=k//2
    if k%2!=0:
        loop=(k//2)+1
    for i in range(1,loop):
        count+=a[i]*a[k-i]
    if(k%2==0):
        count+=(a[k//2]*(a[k//2]-1))//2
    return(count)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        nk = input().split()

        n = int(nk[0])

        k = int(nk[1])

        result = solve(n, k)

        fptr.write(str(result) + '\n')

    fptr.close()
