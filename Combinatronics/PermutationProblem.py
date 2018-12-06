M=10**9+7
L=1002
f=[1]
for i in range(1,L):f.append(f[-1]*i%M)
g=[pow(i,M-2,M)for i in f]
c=lambda n,k:f[n]*g[k]*g[n-k]%M
F=[[]]
for k in range(1,L):
    a=[1]*(k+1)+[0]*(L-k)
    for j in range(1,11):
        a,b=[1],a
        for n in range(L):a.append(j*(a[n]-(b[n-k]*f[n]*g[k]*g[n-k]if n>=k else 0))%M)
    F.append(a)
for _ in [0]*input():
    n,k=map(int,raw_input().split())
    if k*10<n:print 0
    else:print F[min(n,k)][n]*300000003%M
