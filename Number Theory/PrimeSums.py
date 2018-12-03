import random
def isprime(n):
    if n<=1 or n==4 : return False
    if n<=3: return True
    k=10
    while k:
        a=2+random.randint(1,n-4)
        if pow(a,n-1,n)!=1:
            return False
        k-=1
    return True
for _ in range(int(input())):
    n,k=map(int,input().split(' '))
    if n<2*k:
        print('No')
    elif k==1:
        print('Yes' if isprime(n) else 'No')
    elif k==2 and n&1:
        print('Yes' if isprime(n-2) else 'No')
    elif k==2 and n&1==0:
        print('Yes')
    elif k>=3 and n>=2*k:
        print('Yes')
