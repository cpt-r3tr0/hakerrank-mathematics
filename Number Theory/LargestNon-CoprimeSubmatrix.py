#!/bin/python3

import os
import sys

def gcd(a, b):
    a, b = max(a, b), min(a, b)
    while b != 0:
        a, b = b, a%b
    return a

# Complete the solve function below.
def solve(matrix):
    best = 0
    nrows, ncols = len(matrix), len(matrix[0])
    for irow in range(nrows):
        for icol in range(ncols):
            upperrow = [matrix[irow][icol]] * (ncols - icol)
            cur = matrix[irow][icol]
            for jrow in range(irow, nrows):
                prev = matrix[irow][icol]
                goodcols = 0
                for jcol in range(icol, ncols):
                    prev = gcd(prev, gcd(upperrow[jcol-icol], matrix[jrow][jcol]))
                    if prev == 1:
                        upperrow[jcol-icol:] = [1] * (ncols - jcol)
                        break
                    goodcols += 1
                    upperrow[jcol-icol] = prev
                if best >= (nrows-irow) * goodcols:
                    break
                best = max(best, (jrow-irow+1)*goodcols)
    return best

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    matrix = []

    for _ in range(n):
        matrix.append(list(map(int, input().rstrip().split())))

    result = solve(matrix)

    fptr.write(str(result) + '\n')

    fptr.close()
