# Enter your code here. Read input from STDIN. Print output to STDOUT

import functools

def intmatvecmul(M,v,N,mod):
    out = []
    for i in range(N):
        acc = 0
        for j in range(N):
            acc = (acc + M[i][j] * v[j]) % mod
        out.append(acc)
    return out
def intmatmul(A,B,N,mod):
    out = []
    for i in range(N):
        row = []
        for j in range(N):
            acc = 0
            for k in range(N):
                acc = (acc + A[i][k] * B[k][j]) % mod
            row.append(acc)
        out.append(row)
    return out
def eye(N):
    out = []
    for i in range(N):
        row = []
        for j in range(N):
            if i == j:
                row.append(1)
            else:
                row.append(0)
        out.append(row)
    return out
def intmatpow(A,pwr,N,mod):
    #print("in intmatpow")
    tmp = A
    k = 1
    if pwr % 2 == 1:
        pwr -= 1
        acc = A
    else:
        acc = []
    while pwr > 0:
        tmp = intmatmul(tmp,tmp,N,mod)
        if pwr % 2**(k+1) != 0:
            pwr -= 2**k
            if acc:
                acc = intmatmul(acc,tmp,N,mod)
            else:
                acc = tmp
        k += 1
    return acc


T = int(input())
for q in range(T):
    NM = [int(x) for x in input().split()]
    N = NM[0]
    M = NM[1]
    def nxt(i):
        if i == N-1:
            return 0
        else:
            return i + 1
    def prev(i):
        if i == 0:
            return N-1
        else:
            return i - 1


    stepmatrices = []
    for i in range(N):
        m = eye(N)
        m[i][prev(i)] = 1
        m[i][nxt(i)] = 1
        stepmatrices.append(m)
    #Nstepmatrix = functools.reduce(lambda A,B: intmatmul(B,A,N,1000000007),stepmatrices)
    Nstepmatrix = eye(N)
    for i in range(N):
        for j in range(N):
            Nstepmatrix[i][j] += Nstepmatrix[(i-1)%N][j] + Nstepmatrix[(i+1)%N][j]
    numbigsteps = M // N - 1
    numsmallsteps = M % N + N
    hugestepmatrix = intmatpow(Nstepmatrix,numbigsteps,N,1000000007)
    ai = [int(x) for x in input().strip().split()]
    for x in range(N):
        state = ai.copy()
        if numbigsteps >= 1:
            for i in range(x,N):
                state[i] = (state[i] + state[prev(i)] + state[nxt(i)]) % 1000000007
                #state = intmatvecmul(stepmatrices[i],state,N,1000000007)
            state = intmatvecmul(hugestepmatrix,state,N,1000000007)
            for i in range(numsmallsteps - N + x):
                state[i%N] = (state[i%N] + state[(i-1)%N] + state[(i+1)%N]) % 1000000007
                #state = intmatvecmul(stepmatrices[i % N],state,N,1000000007)
        else:
            count = 0
            i = x
            while count < M:
                #state = intmatvecmul(stepmatrices[i],state,N,1000000007)
                state[i%N] = (state[i%N] + state[(i-1)%N]+ state[(i+1)%N]) % 1000000007
                count += 1
                i = nxt(i)
        print(" ".join(map(str,state)))

    print()
