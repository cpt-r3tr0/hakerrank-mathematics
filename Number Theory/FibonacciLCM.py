#!/bin/python3

import fractions, sys


MOD = 1000000007
FIB_MATRIX = [[1, 1], [1, 0]]


def matrix_mult(A, B):
    return [[sum(a * b for a, b in zip(A_row, B_col)) % MOD for B_col in zip(*B)] for A_row in A]

def matrix_exp(A, N):
    M = [[1, 0], [0, 1]]

    if N == 0:
        return M
    elif N == 1:
        return A
    else:
        P = matrix_exp(A, N // 2)
        P = matrix_mult(P, P)

        if N % 2 == 1:
            P = matrix_mult(P, A)

        return P

def fibonacci(N):
    return matrix_exp(FIB_MATRIX, N)[1][0]

def modinv(n):
    return pow(n, MOD - 2, MOD)


memo = {}

def lcm(A, k, i):
    if (k, i) not in memo:
        if i == 0:
            memo[(k, i)] = 1
        else:
            gcd = fractions.gcd(k, A[i - 1])

            if gcd == k:
                memo[(k, i)] = fibonacci(gcd) % MOD
            else:
                memo[(k, i)] = fibonacci(gcd) * lcm(A, k, i - 1) * modinv(lcm(A, gcd, i - 1)) % MOD

    return memo[(k, i)]


if __name__ == '__main__':
    N = int(sys.stdin.readline())
    A = list(set(int(sys.stdin.readline()) for _ in range(N)))

    print(lcm(A, 0, len(A)))
