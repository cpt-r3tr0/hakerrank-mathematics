# Enter your code here. Read input from STDIN. Print output to STDOUT

N, D = map(int, input().split())
N2 = N*N
board = 0
for i in range(N):
   row = [int(x) for x in input().split()]
   for j in range(N):
      if row[j]:
         board |= 1 << (i*N + j)
bits = []
for i in range(N):
   for j in range(N):
      x = 1 << (i*N + j + N2)
      for m in range(N):
         for n in range(N):
            if abs(i-m) + abs(j-n) <= D:
               x |= 1 << (m*N + n)
      bits.append(x)
rank = 0
for i in range(N2):
   b = 1 << i
   j = rank
   while j < N2 and (bits[j] & b) == 0: j += 1
   if j >= N2: continue
   piv = bits[j]
   if board & b: board ^= piv
   if j > rank:
      bits[j] = bits[rank]
      bits[rank] = piv
   rank += 1
   for j in range(rank,N2):
      if bits[j] & b:
         bits[j] ^= piv
if board & ((1 << N2)-1):
   print('Impossible')
else:
   print('Possible')
   flips = []
   for i in range(N2):
      if board & (1 << (i + N2)):
         flips.append(divmod(i,N))
   print(len(flips))
   for f in flips:
      print(*f)
