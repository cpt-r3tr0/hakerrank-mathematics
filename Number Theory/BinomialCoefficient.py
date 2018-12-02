for _ in range(int(input())):
    n,m=list(map(int,input().split()))
    s,d=n+1,1
    while n:
        d,n=d*(n%m+1),n//m
    print(s-d)

    
