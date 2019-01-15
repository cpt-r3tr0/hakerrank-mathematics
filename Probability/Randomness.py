from collections import defaultdict
from itertools import count
N, Q = map(int, raw_input().split())
B = 8
S = list(raw_input().strip())
counts = [0]*10**7
ids = defaultdict(count().next)
ANS = N*(N+1)/2
for j in xrange(N):
  id = -1
  for i in xrange(j,min(j+B,N)):
    id = ids[id,S[i]]
    if counts[id]!=0: ANS-=1
    counts[id]+=1
for _ in xrange(Q):
  P, C = raw_input().split()
  P = int(P)-1
  for j in xrange(max(0,P-B+1),P+1):
    id = -1
    for i in xrange(j,min(j+B,N)):
      id = ids[id,S[i]]
      counts[id]-=1
      if counts[id]==0: ANS-=1
  S[P] = C
  for j in xrange(max(0,P-B+1),P+1):
    id = -1
    for i in xrange(j,min(j+B,N)):
      id = ids[id,S[i]]
      if counts[id]==0: ANS+=1
      counts[id]+=1
  print ANS

  
