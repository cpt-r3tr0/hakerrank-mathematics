#!/bin/python3

import sys
import math

def power(p,z,b,c,q):
    cp=0
    while q%p==0:
        cp+=1
        q/=p
    t=q-1
    exponent=((pow(b,c,t)*z)%t+t-(cp%t))%t
    return pow(p,cp)*pow(p,exponent,q)
def solve(a,b,c,q):
    result=1
    p=2
    while p**2<=a:
        z=0
        while a%p==0:
            a/=p
            z+=1
        if z!=0:
            result*=power(p,z,b,c,q)
            result%=q
        p+=1
    if a!=1:
        result*=power(a,1,b,c,q)
    return result%q
def towerColoring(n):
    return solve(3,3,n,1000000007)

n = int(input().strip())
result = towerColoring(n)
print(result)
