#!/bin/python3

import os
import sys
import math

def find_prime(m):
    high = int(math.sqrt(m)) + 1
    mark = [1] * (high)
    for i in range(2, high):
        j = i * i
        while j <= high - 1:
            if j % i == 0 :
                mark[j] = 0
            j += i
    prime = []
    for i in range(2, high):
        if mark[i] == 1 :
            prime.append(i)

    return prime
# Complete the solve function below.
def solve(n, m):
    prime = find_prime(m)
    arr = [1] * (m - n + 1)
    for i in range(len(prime)):
        low = (n//prime[i]) * prime[i]
        if low < n :
            low += prime[i]
        j = low
        if j == prime[i] :
            j += prime[i]
        while j <= m:
            if j % prime[i] == 0 :
                arr[j - n] = 0
            j += prime[i]
    this_prime = []
    for i in range(0, m - n + 1):
        if arr[i] == 1 :
            this_prime.append(i)
    count = 0
    for i in range(1, len(this_prime)):
        if this_prime[i] - this_prime[i - 1] == 2:
            count += 1
    return count

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    result = solve(n, m)

    fptr.write(str(result) + '\n')

    fptr.close()
