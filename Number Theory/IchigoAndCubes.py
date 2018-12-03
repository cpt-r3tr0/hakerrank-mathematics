# Enter your code here. Read input from STDIN. Print output to STDOUT
from math import ceil
for _ in range(int(input())):
    p, q, r = map(int, input().split())
    print((p*q + p*r + q*r - 1) // 2 % 1000000007)
