#!/bin/python3

import os
import sys
from math import *

# Complete the solve function below.
def mag(x,y):
    return x ** 2 + y ** 2

def toPol(x,y):
    ans = atan2(y,x)
    ans = (ans + 2 * pi) if ans < 0 else ans

    return ans,mag(x,y)

def solve(coordinates):
    return sorted(coordinates, key=lambda p: toPol(p[0],p[1]))


n = int(input())

coordinates = []

for _ in range(n):
    coordinates.append(list(map(int, input().rstrip().split())))

result = solve(coordinates)

print('\n'.join([' '.join(map(str, x)) for x in result]))
