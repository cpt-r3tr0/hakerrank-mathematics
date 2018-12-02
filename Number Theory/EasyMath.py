#!/bin/python3

import os
import sys
import math

# Complete the solve function below.
def solve(x,premier):
    temp=x
    k=0
    while(temp%2==0):
        temp=temp//2
        k+=1
    l=0
    while(temp%5==0):
        temp=temp//5
        l+=1
    b=max(k-2,l)

    decomposition=decomp(temp,premier)

    a=1
    for cle,value in decomposition.items():
        a=lcm(a,a_premier(cle)*(cle**(max(value-1,0))))

    return 2*a+b

def a_premier(temp):
    a=1
    rp=1
    x=1
    while(rp>0):
        x*=10
        x=x%temp
        rp+=x
        rp=rp%temp
        a+=1
    return a

def gcd(a,b):
    if(a<b):return gcd(b,a)
    while b > 0:
        a, b = b, a % b
    return a

def lcm(a, b):
    return (a * b // gcd(a, b))

def decomp(x,premier):
    decomposition={}
    temp=x
    for p in premier:
        ind=0
        while(temp%p==0):
            ind+=1
            temp=temp//p
        if(ind>0):decomposition[p]=ind
        if(temp==1): break
    return decomposition

def premiers():
    MAX_X=10**5+1
    sieve=[i for i in range(MAX_X)]
    sieve[1]=0
    p=2
    for i in range(2*p,MAX_X,p): sieve[i]=0
    for p in range(3,MAX_X,2):
        for i in range(2*p,MAX_X,p): sieve[i]=0

    return list(filter(lambda x: x > 0, sieve))


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    premier=premiers()

    for t_itr in range(t):
        x = int(input())

        result = solve(x,premier)

        fptr.write(str(result) + '\n')

    fptr.close()
