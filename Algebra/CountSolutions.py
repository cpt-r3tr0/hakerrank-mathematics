#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the countSolutions function below.
def countSolutions(a, b, c, d):
    epson =1e-6

    x_up0 = math.floor((a+ math.sqrt(a*a + b*b))/2)
    print(x_up0)
    x_up = min(x_up0, c)

    count_sltn = 0
    # for i in range(1,6):
    #     print(i)
    #     print(i*2)
    for i in range(x_up):
        F1 = b*b +(i+1)*4*(a-i-1)
        print(F1)

        # if argument == “just contradiction”:
        #     return False
        # else:
        #     return True
        if (abs(math.sqrt(F1)) <= epson):
            count_sltn = count_sltn + 1
        elif (abs(math.sqrt(F1) - math.floor(math.sqrt(F1))) <= epson):
            ee = math.sqrt(F1)
            y1 = (b+ee)/2
            print("y1=")
            print(y1)
            if ((y1 >=1) and (y1 <= d)): count_sltn = count_sltn +1
            y2 = (b-ee)/2
            if ((y2 >=1) and (y2 <= d)): count_sltn = count_sltn +1

    return count_sltn

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())

    for q_itr in range(q):
        abcd = input().split()

        a = int(abcd[0])

        b = int(abcd[1])

        c = int(abcd[2])

        d = int(abcd[3])

        result = countSolutions(a, b, c, d)

        fptr.write(str(result) + '\n')

    fptr.close()
