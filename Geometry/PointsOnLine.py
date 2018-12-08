#!/bin/python3

n = int(input())
x = [0]*n
y = [0]*n
for i in range(n):
    x[i], y[i] = map(int, input().split())
if min(x) == max(x) or min(y) == max(y):
    print('YES')
else:
    print('NO')
