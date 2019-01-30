#!/bin/python3

import os
import sys

def orientation(a,b,c):
    area = (b[1] - a[1]) * (c[0] - b[0]) - (b[0] - a[0]) * (c[1] - b[1])
    return 0 if area == 0 else 1 if area > 0 else -1

def between1(a,b,c):            # dim=1
    return (a <= b <=c) or (a >= b >= c)

def between2(a,b,c):            # dim=2
    return between1(a[0],b[0],c[0]) and between1(a[1],b[1],c[1])

def intersect_p(a,b,c,d):
    o1 = orientation(a,b,c)
    if o1 == 0:
        return between2(a,c,b)
    o2 = orientation(a,b,d)
    if o2 == 0:
        return between2(a,d,b)
    o3 = orientation(c,d,a)
    if o3 == 0:
        return between2(c,a,d)
    o4 = orientation(c,d,b)
    if o4 == 0:
        return between2(c,b,d)
    return o1 != o2 and o3 != o4

# Complete the solve function below.
def solve(x1, y1, x2, y2, xm, ym):
    return "NO" if intersect_p((0,0),(xm,ym),(x1,y1),(x2,y2)) else "YES"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        x1Y1X2Y2XmYm = input().split()

        x1 = int(x1Y1X2Y2XmYm[0])

        y1 = int(x1Y1X2Y2XmYm[1])

        x2 = int(x1Y1X2Y2XmYm[2])

        y2 = int(x1Y1X2Y2XmYm[3])

        xm = int(x1Y1X2Y2XmYm[4])

        ym = int(x1Y1X2Y2XmYm[5])

        result = solve(x1, y1, x2, y2, xm, ym)

        fptr.write(result + '\n')

    fptr.close()
