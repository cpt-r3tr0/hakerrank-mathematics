#!/bin/python3

for _ in range(int(input())):
    n, sum, cur = int(input()), 0, 1
    while (cur <= n):
        sum+=pow(2, cur, 10)
        cur*=2
    sum = sum * (1 + (4 if n%2==1 else 0)) % 10
    print(sum)
