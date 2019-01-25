# Enter your code here. Read input from STDIN. Print output to STDOUT

mod = 1000000007
t=input()
assert t<=10 and t>=1
for _ in range(t):
    k = input()
    n = input()
    r = input()%mod
    assert k<=1000 and k>=1
    assert n<=10**16 and n>=1
    assert r>=2 and r<=10**16
    assert r%mod !=1
    if n<k:
        sum1 = 0
        for i in range(1,n+1):
            sum1+=((   pow(i,k,mod)   ) * (   pow(r,i,mod)   ))%mod
        print sum1%mod

    else:
        matrix=[]
        matrix2=[]
        for _ in range(k+1):
            t=[]
            for _ in range(k+1):
                t.append(0)
            matrix.append(t)
        for _ in range(k):
            t=[]
            for _ in range(k+2):
                t.append(0)
            matrix2.append(t)


        for i in range(1,k+1):
            matrix[0][i] = pow(i,k,mod)

        for i in range(1,k+1):
            matrix2[0][i] = pow(n-k+i,k,mod)

        for i in range(1,k):
            for j in range(1,k+3-i):
                matrix2[i][j-1] = (matrix2[i-1][j] - matrix2[i-1][j-1])%mod

        for i in range(1,k+1):
            for j in range(1,k+1):
                matrix[i][j] = (matrix[i-1][j] - matrix[i-1][j-1])%mod
        coef1 = matrix[-1][1:]
        coef2 = []
        r_l = []
        for i in range(1,k):
            r_l.append(pow(r,i,mod))
        for i in range(k):
            coef2.append(matrix2[i][k-i])
        sum1 = 0
        for i,j in zip(r_l,coef1):
            sum1 += (i*j)%mod

        sum1 += (coef1[-1]*pow(r,k,mod)*( pow(r,(n-k+1),mod) - 1)*pow((r-1),mod-2,mod))%mod

        temp = k
        for i in coef2:
            if temp%2==1:
                sum1-=((i * pow(r,n+1,mod) ) * pow(r-1,temp-1))%mod
            else:
                sum1+=((i * pow(r,n+1,mod) ) * pow(r-1,temp-1))%mod
            temp-=1
        print sum1*pow(pow(1-r,k,mod),mod-2,mod)%mod
    
