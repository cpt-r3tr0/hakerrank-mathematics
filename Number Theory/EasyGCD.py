#!/bin/python3

import sys

from math import sqrt
from fractions import gcd

def desintegrate(n):
    res = []
    for i in range(1,int(sqrt(n)) + 1):
        if n % i == 0:
            res.append(i)
            res.append(n//i)
    return sorted(res)[1:]

def setgcd(a):
    res = []
    lst = desintegrate(a[0])
    for i in lst:
        h = True
        for j in a[1:]:
            if j % i != 0:
                h = False
                break
        if h:
            res.append(i)
            return res
    return res


n,k = input().strip().split(' ')
n,k = [int(n),int(k)]
A = [int(A_temp) for A_temp in input().strip().split(' ')]
x = setgcd(A)

print(max([k - (k % i) for i in x]))
