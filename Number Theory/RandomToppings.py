#!/bin/python3

import os
import sys


def C(n, k, mod, inv):
    if k > n:
        return 0

    res = 1
    for i in range(n, n - k, -1):
        res *= i
        res %= mod

    for i in range(1, k + 1):
        res *= inv[i]
        res %= mod

    return res

def powmod(x, n, mod):
    res = 1
    while n:
        if (n % 2) == 1:
            res = (res * x) % mod
        x = (x * x) % mod
        n //= 2
    return res

def CL(n, k, mod):
    inv = [0, 1]

    for i in range(2, mod):
        inv.append((mod - (mod // i)) * inv[mod % i] % mod)

    res = 1
    while n or k:
        res = (res * C(n % mod, k % mod, mod, inv)) % mod
        n //= mod
        k //= mod

    return res

def factorize(x):
    res = []

    i = 2
    while x > 1:
        if (x % i) == 0:
            res.append(i)
            x //= i
        i += 1

    return res

# Complete the solve function below.
def solve(n, r, m):
    fa = factorize(m)
    fa.sort()

    x = []
    for f in fa:
        res = CL(n, r, f)

        for (i, y) in enumerate(fa):
            if (y >= f):
                break
            res = (res + f - x[i]) % f
            res = (res * powmod(y, f - 2, f)) % f

        x.append(res)

    res = 0
    for i in range(len(x)):
        curr = 1
        for j in range(i):
            curr *= fa[j]
        res += curr * x[i]
        res %= m

    return res

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        nrm = input().split()

        n = int(nrm[0])

        r = int(nrm[1])

        m = int(nrm[2])

        result = solve(n, r, m)

        fptr.write(str(result) + '\n')

    fptr.close()
