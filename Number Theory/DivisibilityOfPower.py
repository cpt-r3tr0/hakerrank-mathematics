#!/bin/python3

import os
import sys

from math import gcd, log

# Complete the solve function below.
def min_pow(a, b):
    k = 0
    while a > 1:
        k = k + 1
        a = gcd(a, b)
        b = b // a
    if b == 1:
        return k - 1
    else:
        return -1

def is_enough_1(a, i, j, k):
    alpha = a[i] if i <= j else 1
    if alpha == 0:
        res = k == 0
    else:
        res = k <= 1
    if res or alpha <= 1:
        cont = False
    else:
        cont = True
    l = i + 1
    while cont:
        if l > j:
            c = 1
        else:
            c = a[l]
        if c == 0:
            res = k <= 1
            cont = False
        elif c == 1:
            res = k <= alpha
            cont = False
        else:
            res = k <= alpha
            if res:
                cont = False
            else:
                k = log(k) / log(alpha)
                alpha = c
                l = l + 1
    return res

def is_enough_10(a, i, j, k):
    # print('enough: a = %s -- k = %d'%(a[i:j+1], k))
    if i > j:
        coeff = [1]
    elif a[i] <= 1:
        coeff = [a[i]]
    else:
        coeff = [a[i]]
        for c in a[i+1:j+1]:
            if c == 0:
                coeff.pop()
                if coeff == []:
                    coeff = [1]
                    break
            elif c == 1:
                break
            else:
                coeff.append(c)
    if coeff[0] == 0:
        alpha = 0
        cont = False
    else:
        alpha = 1
        cont = True
    l = 0
    if k <= alpha:
        cont = False
    else:
        cont = True
    while cont and l < len(coeff):
        if coeff[l] <= 1:
            # print('a[l] <= 1')
            cont = False
        else:
            # print('else')
            k = log(k) - log(alpha)
            alpha = log(a[l])
            cont = k > alpha
            l = l + 1
    if k <= alpha:
        return True
    else:
        return False

def is_enough_2(a, i, j, k):
    alpha = a[i]
    l = i + 1
    cont = True
    while cont and l <= j:
        if alpha == 0:
            cont = False
        elif alpha == 1:
            cont = False
        elif k <= 0:
            cont = False
        else:
            k = log(k) / log(alpha)
            alpha = a[l]
            l = l + 1
            if k <= alpha:
                cont = False
    if k <= alpha:
        return True
    else:
        return False

def find(i, j, a):
    if i > j:
        return 1
    else:
        return a[i] ** find(i + 1, j, a)

def solve(a, queries):
    result = []
    for q in queries:
        i = q[0] - 1
        j = q[1] - 1
        x = q[2]
        if i > j or a[i] == 1:
            if x == 1:
                result.append('Yes')
            else:
                result.append('No')
        elif a[i] == 0:
            result.append('Yes')
        else:
            k = min_pow(a[i], x)
            if k == -1:
                result.append('No')
            else:
                res = is_enough_1(a, i + 1, j, k)
                if res:
                    result.append('Yes')
                else:
                    result.append('No')
    return result


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a_count = int(input())

    a = list(map(int, input().rstrip().split()))

    q = int(input())

    queries = []

    for _ in range(q):
        queries.append(list(map(int, input().rstrip().split())))

    result = solve(a, queries)

    fptr.write('\n'.join(result))
    fptr.write('\n')

    fptr.close()
