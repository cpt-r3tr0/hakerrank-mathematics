import math
N=int(input())
n=N
prime = [True for i in range(n+1)]
p = 2
while (p * p <= n):
    if (prime[p] == True):
        for i in range(p*p, n+1, p):
            prime[i] = False
    p += 1
div=1
for p in range(2,n+1):
    if prime[p]:

        t=n//p
        sum=t
        while t!=0:
            t=t//p
            sum=sum+t
        div=div*(2*sum+1)
print(div%1000007)
