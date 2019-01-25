# Enter your code here. Read input from STDIN. Print output to STDOUT

mod = 10**9 + 7
N = int(input())
A = [int(x) for x in input().split()]
M = int(input())
C = []
for i in range(20):
   R = [0]
   t = 0
   for x in A:
      t += (x >> i) & 1
      R.append(t)
   C.append(R)
for m in range(M):
   K, P, R = map(int, input().split())
   d = R - P + 1
   t = 0
   for i in range(20):
      n1 = C[i][R] - C[i][P-1]
      n0 = d - n1
      if (K >> i) & 1:
         x = (n1 * (n1 - 1) + n0 * (n0 - 1)) >> 1
      else:
         x = n1 * n0
      t = (t + (x << i)) % mod
   print(t)
