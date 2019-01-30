#!/bin/python3

import os
import sys

# Complete the solve function below.
def solve(friends):
    m=len(friends[0]);n=len(friends)
    return([sorted(friends,key=lambda x:x[i])[(n+1)//2-1][i] for i in range(m)])

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    friends = []

    for _ in range(n):
        friends.append(list(map(int, input().rstrip().split())))

    result = solve(friends)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
