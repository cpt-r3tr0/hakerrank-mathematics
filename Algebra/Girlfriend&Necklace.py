# Enter your code here. Read input from STDIN. Print output to STDOUT
def matrix_multiply(a,b, mod = 0):
    M = len(a)
    if(M == 0): return []
    P = len(a[0])
    if(len(b) != P or P == 0 or len(b) == 0): return []
    N = len(b[0])
    if(N == 0): return []
    prod = [[0 for i in xrange(N)] for j in xrange(M)]
    for i in xrange(M):
        for j in xrange(N):
            for L in xrange(P):
                prod[i][j] += a[i][L] * b[L][j]
            if(mod >= 2):
                prod[i][j] %= mod
    return prod
m_m = matrix_multiply

def matrix_exponentiation(M,exp,mod):
    L = len(M)
    id_m = [[0 for i in xrange(L)] for j in xrange(L)]
    for i in xrange(L):
        id_m[i][i] = 1
    while(exp > 0):
        if(exp % 2 == 1):
            id_m = matrix_multiply(id_m,M,mod)
        M = matrix_multiply(M,M,mod)
        exp /= 2
    return id_m

m_e = matrix_exponentiation

MOD = 1000000007

#RB, BR, RR
mat = [[0,0,1],[1,0,0],[0,1,1]]

T = int(input())
for i in xrange(T):
    N = int(input())
    s = m_e(mat,N-2,MOD)
    print sum([sum(x) for x in s]) % MOD
