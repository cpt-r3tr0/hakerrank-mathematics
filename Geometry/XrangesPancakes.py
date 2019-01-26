#!/bin/python3

import os
import sys

# Complete the solve function below.
n = 0
def solve(operations):
    s = 0
    t = 0
    for operation in operations:
        if operation[0] == 1: # rotate
            t += operation[1]
        else: # flip
            s = 1 - s
            t = operation[1] - t
    if s == 0:
        action = 1
        value = (n - t) % n
    else:
        action = 2
        value = t % n
    return action, value


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    operations = []

    for _ in range(m):
        operations.append(list(map(int, input().rstrip().split())))

    result = solve(operations)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
