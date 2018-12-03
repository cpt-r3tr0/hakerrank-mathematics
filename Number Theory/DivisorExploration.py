#!/bin/env python

from __future__ import division, print_function
import sys


MOD = 1000000007
MAX_N = 2 * 10**5 + 1


def modinv(n):
    return pow(n, MOD - 2, MOD)


if __name__ == "__main__":
    D = int(sys.stdin.readline())

    # Precalculate products of consecutive numbers
    product = [1, 1]

    for i in range(2, MAX_N + 1):
        product.append(i * product[-1] % MOD)


    for _ in range(D):
        m, a = list(map(int, sys.stdin.readline().split()))

        total = product[a + m + 1] * modinv(product[a + 2]) % MOD
        total = (a + 2) * pow(total, 2, MOD) * (a + m + 2) % MOD
        total = total * modinv(pow(2, m, MOD)) % MOD

        print(total)
