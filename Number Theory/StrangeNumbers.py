import bisect
strange = list(range(10))
p = 10
for d in range(2,19):
   i = bisect.bisect_left(strange, (p + d - 1) // d)
   p *= 10
   while i < len(strange):
      x = d * strange[i]
      if x >= p: break
      strange.append(x)
      i += 1
T = int(input())
for t in range(T):
   L, R = map(int, input().split())
   print(bisect.bisect_left(strange, R+1) - bisect.bisect_left(strange, L))
