#!/bin/python3

import math
import os
import random
import re
import sys
from functools import reduce
from fractions import gcd

def chosen_one(n, a):
    if n == 1:
        return a[0] + 1
    else:
        a_set = set(a)
        a_set = list(a_set)
        n = len(a_set)
        if n == 2:
            if a.count(a_set[0]) > 1:
                return a_set[0]
            else:
                return a_set[1]
        else:
            z = a_set[0]
            l_r = [z]
            for i in range(n-1):
                z = gcd(z, a_set[i+1])
                l_r.append(z)
            x = a_set[-1]
            r_l = [x]
            for i in range(-1, -n, -1):
                x = gcd(x, a_set[i-1])
                r_l.append(x)
            res = 0
            r_l = r_l[::-1]
            for i in range(1, n - 1):
                if a_set[i] % gcd(l_r[i-1], r_l[i+1]) != 0:
                    res = i
                    return gcd(l_r[res - 1], r_l[res + 1])
            if a_set[0] % r_l[1] != 0:
                return r_l[1]
            if a_set[-1] % l_r[-2] != 0:
                return l_r[-2]

if __name__ == '__main__':
    n = int(input())

    a = list(map(int, input().rstrip().split()))

    print (chosen_one(n,a))
    # Write Your Code Here
