#!/bin/python3

import math
import os
import random
import re
import sys



if __name__ == '__main__':
    wh = input().split()

    w = int(wh[0])

    h = int(wh[1])

    circleXCircleY = input().split()

    circleX = int(circleXCircleY[0])

    circleY = int(circleXCircleY[1])

    r = int(circleXCircleY[2])

    x1Y1X3Y3 = input().split()

    x1 = int(x1Y1X3Y3[0])

    y1 = int(x1Y1X3Y3[1])

    x3 = int(x1Y1X3Y3[2])

    y3 = int(x1Y1X3Y3[3])

    # Write Your Code Here
    mesh = [['.' for i in range(w)] for j in range(h)]

    c1,c2 = (x1+x3)/2 , (y1+y3)/2
    dist = math.sqrt((x3-x1)**2 + (y3-y1)**2)
    sino = (y3-y1)/dist
    coso = (x3-x1)/dist
    for y in range(h):
        s=''
        for x in range(w):
            c='.'
            xn = (x-c1)*coso + (y-c2)*sino
            yn = -(x-c1)*sino + (y-c2)*coso
            if (math.fabs(xn)+math.fabs(yn)<=dist/2):
                c='#'
            if ((x-circleX)**2 + (y-circleY)**2 <= r**2):
                c='#'
            if (x==x1) and (y==y1):
                c='#'
            if (x==x3) and (y==y3):
                c='#'
            if (x==c1+(y3-y1)/2) and (y==c2-(x3-x1)/2):
                c='#'
            if (x==c1-(y3-y1)/2) and (y==c2+(x3-x1)/2):
                c='#'
            s=s+c
        print(s)
