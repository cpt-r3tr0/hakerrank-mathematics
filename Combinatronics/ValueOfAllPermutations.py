# Enter your code here. Read input from STDIN. Print output to STDOUT

P = input()

# collect and sort A
N = input()
A = map(int, raw_input().strip().split())
A.sort()

# calculate partial sums S
S = [0]*(N+1)
for i in xrange(N):
    S[i+1] = (S[i] + A[i]) % P

# inverses mod P
inv = [1]*(N+2)
for i in xrange(2,N+2):
    inv[i] = -(P/i) * inv[P%i] % P

# calculate number of distinct permutations
perms = 1
count = 1
for i in xrange(1,N):
    if A[i] != A[i-1]:
        count = 0
    count += 1
    perms *= inv[count] * (i+1)
    perms %= P

# process queries
Q = input()
for cas in xrange(Q):
    M = input()

    # binary search
    h, i = -1, N
    while i - h > 1:
        j = h + i >> 1
        if A[j] <= M:
            h = j
        else:
            i = j

    # at this point, A[i-1] <= M < A[i]
    print S[i] * perms * inv[N-i+1] % P
