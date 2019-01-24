#!/bin/python

from math import floor
from math import sqrt

m = 10**9 + 7

def square(n):
    if n < 0:
        return False
    sqn = floor(sqrt(n))
    return sqn * sqn == n

def solve(f2, f3, f4):
    a = -1
    b = -1
    c = -1
    for _a in xrange(1, 15001):
        x = f2 - _a**2
        y = f3 - _a**3
        z = f4 - _a**4
        d = 2 * z - x**2
        if square(d):
            c = int(x - sqrt(d))
            if not (c & 1):
                c /= 2
                b = x - c
                if square(b):
                    b = sqrt(b)
                    c = sqrt(c)
                    if _a < b and b**3 + c**3 == y:
                        a = _a
        if a != -1:
            break
    return (a, b, c)

def gp_sum(a, l, r):
    if a == 1:
        return r - l + 1
    return ((pow(a, r + 1, m) - pow(a, l, m) + m) % m * pow(a - 1, m - 2, m)) % m

for _ in xrange(int(raw_input())):
    f2, f3, f4, l, r = map(int, raw_input().split())
    a, b, c = map(int, solve(f2, f3, f4))
    print (gp_sum(a, l, r) + gp_sum(b, l, r) + gp_sum(c, l, r)) % m
