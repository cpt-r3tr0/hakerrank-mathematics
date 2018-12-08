#!/bin/python3

import sys

mod = 10 ** 9 + 9

B = [0 for _ in range(1001)]
inv = [i for i in range(10001)]
fac = [i for i in range(10001)]
fac[0] = 1

for i in range(1, 10001):
    inv[i] = pow(i, mod-2, mod)

for i in range(1, 10001):
    fac[i] = fac[i-1] * i
    fac[i] %= mod

invfac = fac[:]
for i in range(len(invfac)):
    invfac[i] = pow(invfac[i], mod-2, mod)

def comb(n, k):
    return fac[n] * invfac[n-k] * invfac[k] % mod

B[0] = 1
B[1] = (mod-1) * pow(2, mod-2, mod) % mod

for m in range(2, 1001):
    for k in range(m):
        B[m] -= comb(m, k) * B[k] * inv[m - k + 1] % mod
        B[m] %= mod

B[1] = mod - B[1]

def f(n, p):
    """Sum of pth powers of numbers 1 to n"""
    res = 0
    for k in range(p+1):
        res += comb(p,k) * B[p-k] * pow(n, k+1, mod) * inv[k+1] % mod
        res %= mod
    return res

def highwayConstruction(n, k):
    if n <= 2: return 0
    return (f(n-1, k) + mod - 1) % mod

if __name__ == "__main__":
    q = int(input().strip())
    for a0 in range(q):
        n, k = input().strip().split(' ')
        n, k = [int(n), int(k)]
        result = highwayConstruction(n, k)
        print(result)
