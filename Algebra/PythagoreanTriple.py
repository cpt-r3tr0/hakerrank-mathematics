#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the pythagoreanTriple function below.
def pythagoreanTriple(a):
    if a%2 == 0:
        # a = 2mn
        m, n = a//2, 1
        return [a, m**2-n**2, m**2+n**2]
    else:
        # a = (m-n)(m+n)
        m = (a+1)//2
        n = (a-1)//2
        return [a, 2*m*n, m**2+n**2]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a = int(input())

    triple = pythagoreanTriple(a)

    fptr.write(' '.join(map(str, triple)))
    fptr.write('\n')

    fptr.close()
