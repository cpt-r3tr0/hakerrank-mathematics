#/usr/bin/python
global div_arr
global mod
mod = 10**9 + 7
div_arr=[0]*1000000
div_arr[1]=1;div_arr[2]=1;div_arr[3]=1

for i in range(2,1000000):
    if div_arr[i]==0:
        div_arr[i]=1
    if div_arr[i]>1:
        continue
    for j in range(2*i,1000000,i):
        if div_arr[j]==0:
            div_arr[j]=i

def factors(n):
    while (n!=1 and div_arr[n]!=1):
        yield div_arr[n]
        n/=div_arr[n]
    yield n

def totient(n):
    if n==1:
        return 1
    f={}
    for i in factors(n):
        if i in f:
            f[i]+=1
        else:
            f[i]=1
    return reduce (lambda x,y:(x*y)%mod,map (lambda x: ((x[0]**(x[1]-1))*(x[0]-1))%mod,[ [k,v] for k,v in f.iteritems()] ))

for _ in range(input()):
    k=input()
    n_val=map(int,raw_input().split())
    sig=0
    for d in range(1,min(n_val)+1):
        prod=totient(d)* reduce (lambda x,y: (x*y)%mod, map(lambda x: x/d,n_val))
        sig=(sig+prod)%mod
    print sig%mod
    
