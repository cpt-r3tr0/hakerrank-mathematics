#!/bin/python3

import os
import sys

def primes_sieve2(limit):
    a = [True] * limit
    a[0] = a[1] = False

    for (i, isprime) in enumerate(a):
        if isprime:
            yield i
            for n in range(i*i, limit, i):     # Mark factors non-prime
                a[n] = False

def adder(n):
    s=0
    for i in str(n):
        s=s+int(i)
    return(s)
# Complete the solve function below.
def solve(n):
    l=2
    n2=n
    i=0
    out=0
    while(n2!=1):
        if(n2%l==0):
            n2=n2//l
            out=out+adder(l)
        else:
            l=l+1
    s=adder(n)

    if(s==out):
        return(1)
    else:
        return(0)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    result = solve(n)

    fptr.write(str(result) + '\n')

    fptr.close()
