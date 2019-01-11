MOD=10**9+7

A,B,T=map(int,input().split())
D=(A+B)//2
R=1
while T > 0:
    if T % 2:
        R = (R*D) % MOD
    D = (D*D) % MOD
    T //= 2

print(R)
