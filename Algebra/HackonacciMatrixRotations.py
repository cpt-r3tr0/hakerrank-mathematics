#!/bin/python3

n, q = map(int, input().split())
H = (1, 1, 0, 1, 0, 0, 1)
M = tuple(tuple(H[(i*i*j*j) % 7] for j in range(1,n+1)) for i in range(1,n+1))
R = M
D = [0] * 4
for r in range(1,4):
   R = tuple(tuple(R[j][i] for j in range(n-1,-1,-1)) for i in range(n))
   d = 0
   for i in range(n):
      a = M[i]
      b = R[i]
      for j in range(n):
         d += a[j] ^ b[j]
   D[r] = d
for Q in range(q):
   a = int(input())
   print(D[a//90&3])
