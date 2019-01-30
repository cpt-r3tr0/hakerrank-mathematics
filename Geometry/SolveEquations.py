#!/bin/python3

import os
import sys

# Complete the solve function below.
def mygcd(a, b):
    if a == 1 or b == 1:
        return 1
    else:
        a, b = max(a, b), min(a, b)
        r = a%b
        while r > 0:
            a, b = b, r
            r = a%b
        return b

# Find the solution to the congruence equation
def Prime_Cong(a, b, c):
    # record the sequence of numbers
    if a == 1:
        return (c, 0)
    elif b == 1:
        return (0, c)
    Q = []
    qr = divmod(a, b)
    while qr[1] > 0:
        Q.append(qr[0])
        a, b = b, qr[1]
        qr = divmod(a, b)
    # should end up with b = 1, qr = (a, 0)
    a, b = 1, -Q[-1]
    for q in Q[-2::-1]:
        a, b = b, a - b*q
    return (a*c, b*c)

def solve(a, b, c):
    g = mygcd(a, b)
    # make the simplest case
    a, b, c = a//g, b//g, c//g
    x0, y0 = Prime_Cong(a, b, c)
    t = round((a*c/(a*a+b*b)-x0)/b)
    x, y = x0 + b*t, y0 - a*t
    if x <= 0:
        x, y = x + b, y - a
    return x, y


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        abc = input().split()

        a = int(abc[0])

        b = int(abc[1])

        c = int(abc[2])

        result = solve(a, b, c)

        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')

    fptr.close()
