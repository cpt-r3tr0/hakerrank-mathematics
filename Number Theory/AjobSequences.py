# Enter your code here. Read input from STDIN. Print output to STDOUT

mx=100001
F=[0]*mx
B=[0]*mx

def init(p):
    F[0]=1
    for i in range(1,p):
        F[i]=(F[i-1]*i)%p

    B[p-1]=pow(F[p-1],p-2,p)
    for i in range(p-2,-1,-1):
        B[i]=(B[i+1]*(i+1))%p

def ncr(n,r,p):
    if n<r:return 0
    return (F[n]*B[r]*B[n-r])%p

tt=int(raw_input())
for ii in range(0,tt):
    (n,l,p)=map(int,raw_input().strip().split())
    init(p)

    n+=1
    l+=1
    ans=1

    while n>0 and l>0:
        ans=(ans*ncr(n%p,l%p,p))%p
        n=n/p
        l=l/p
    print ans
