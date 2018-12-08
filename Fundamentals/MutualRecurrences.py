mod = 10**9

for cas in xrange(input()):
    a,b,c,d,e,f,g,h,n = map(int, raw_input().strip().split())

    X = max(a,f,g)
    Y = max(e,b,c)
    XY = X+Y
    XY0 = XY+0
    XY1 = XY+1
    XY2 = XY+2
    XY3 = XY+3

    N = XY+4
    n += 1
    a -= 1
    b -= 1
    c -= 1
    e -= 1
    f -= 1
    g -= 1

    temp = [[0]*N for i in xrange(N)]
    pA = [[0]*N for i in xrange(N)]
    temprow = [0]*N

    def mulA():
        for r in xrange(N):
            pAr = pA[r]
            for j in xrange(N):
                temprow[j] = 0

            temprow[  a] += pAr[0]
            temprow[X+b] += pAr[0]
            temprow[X+c] += pAr[0]
            temprow[XY1] += pAr[0]
            temprow[X+e] += pAr[X]
            temprow[  f] += pAr[X]
            temprow[  g] += pAr[X]
            temprow[XY3] += pAr[X]
            temprow[XY0] += d * pAr[XY0]
            temprow[XY0] += d * pAr[XY1]
            temprow[XY1] += d * pAr[XY1]
            temprow[XY2] += h * pAr[XY2]
            temprow[XY2] += h * pAr[XY3]
            temprow[XY3] += h * pAr[XY3]
            for i in xrange(X-1): temprow[  i] += pAr[  i+1]
            for i in xrange(Y-1): temprow[X+i] += pAr[X+i+1]

            for j in xrange(N):
                pAr[j] = temprow[j] % mod

    def sqr():
        global temp, pA
        for i in xrange(N):
            tempi = temp[i]
            pAi = pA[i]
            for j in xrange(N):
                tempi[j] = 0

            for k in xrange(N):
                pAik = pAi[k]
                if pAik:
                    pAk = pA[k]
                    for j in xrange(N):
                        tempi[j] += pAik * pAk[j]

            for j in xrange(N):
                tempi[j] %= mod

        temp, pA = pA, temp


    def powA(n):
        if n == 0:
            return
        elif n & 1:
            powA(n-1)
            mulA()
        else:
            powA(n/2)
            sqr()

    for i in xrange(N):
        pA[i][i] = 1

    powA(n)

    x = y = 0
    for j in xrange(XY):
        x += pA[0][j]
        y += pA[X][j]
    x += pA[0][XY0] + pA[0][XY2]
    y += pA[X][XY0] + pA[X][XY2]
    x %= mod
    y %= mod

    print x, y
