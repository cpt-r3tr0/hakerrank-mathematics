#!/bin/python3
import functools
import operator

MODULO = 10**9 + 7
MAX_N = 100000


def totient(n):
    "Return a list of Euler's totient numbers less than n."
    totient = list(range(n))
    for i in range(1, n):
        # At this time, totient[i] is ready now.
        for multiply_i in range(i*2, n, i):
            # The amount of number that is co-prime to i is also
            # co-prime to those multipliers of i. Subtract it.
            totient[multiply_i] -= totient[i]
    return totient


def product(iterable, start=1):
    return functools.reduce(operator.mul, iterable, start)


def sum_gcd(nk, totients):
    # Use the fact: Sum_{d|n}{phi(d)} = n
    # http://en.wikipedia.org/wiki/Euler%27s_totient_function#Divisor_sum
    sum = 0
    for gcd in range(1, min(nk)+1):
        sum += (totients[gcd] * product(n//gcd for n in nk))
    return sum


def main():
    totients = totient(MAX_N+1)
    T = int(input())
    for t in range(T):
        K = int(input())
        nk = [int(n) for n in input().split()]
        print(sum_gcd(nk, totients) % MODULO)


if __name__ == '__main__':
    main()
