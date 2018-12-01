#!/bin/python3

import os
import sys
from fractions import gcd


for x in range(int(input())):
    n = int(input())
    a = list(map(int,input().split()))
    print(a[0],end = ' ')
    j = 0
    while j<n-1:
        print(int(a[j]*a[j+1]/gcd(a[j],a[j+1])),end = ' ')
        j += 1
    print(a[n-1])
