#!/bin/python3

import sys
from fractions import gcd
import itertools as it

def phi(n):
    res = n
    i = 2
    while i * i <= n:
        if n % i == 0:
            res -= res // i
        while n % i == 0:
            n //= i
        i += 1
    if n > 1: res -= res // n
    return res

def pfacs(n):
    i = 2
    while i * i <= n:
        if n % i == 0: yield i
        while n % i == 0: n //= i
        i += 1
    if n > 1: yield n

def div_none(ps, n):
    if n == 0: return 0
    res = n
    for l in range(1, len(ps)+1):
        for s in it.combinations(ps, l):
            p = 1
            for val in s: p *= val
            if l % 2 == 1:
                res -= n // p
            else:
                res += n // p
    return res

def coprime(n, r):
    fs = list(pfacs(n))
    p = phi(n)
    res = r // n * p + div_none(fs, r % n)
    return res

n = int(input().strip())
res = 0
for i in range(2, int(n**0.5) + 1):
    l = i
    r = n // i
    #print (i, l, r, coprime(i, r - l))
    res += coprime(i, r - l)
print(res)
