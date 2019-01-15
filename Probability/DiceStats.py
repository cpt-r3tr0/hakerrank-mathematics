# Enter your code here. Read input from STDIN. Print output to STDOUT

def reduce_probs(p):
    probs = [[0 for x in range(6)] for y in range(6)]
    for x in range(6):
        for y in range(6):
            if x == y: continue
            probs[x][y] = p[y] / (1.0 - p[x])
    return probs

def calc_stats(n, probs):
    mean = [[0 for x in range(6)] for y in range(6)]
    var = [[0 for x in range(6)] for y in range(6)]
    if n == 1:
        for x in range(6):
            for y in range(6):
                mean[x][y] = y
        return mean, var, probs

    p = [[0 for x in range(6)] for y in range(6)]
    if n%2 == 1:
        Xm, Xv, Xp = calc_stats(n-1, probs)
        for x in range(6):
            for y in range(6):
                for m in range(6):
                    p[x][y] += Xp[x][m]*probs[m][y]
        for x in range(6):
            for y in range(6):
                for m in range(6):
                    mean[x][y] += (Xm[x][m] + y)*Xp[x][m]*probs[m][y] / p[x][y]
                    var[x][y] += (Xv[x][m])*Xp[x][m]*probs[m][y] / p[x][y]
        for x in range(6):
            for y in range(6):
                for m in range(6):
                    var[x][y] += (Xm[x][m] + y - mean[x][y])**2 *Xp[x][m]*probs[m][y] / p[x][y]
        return mean, var, p

    Xm, Xv, Xp = calc_stats(n//2, probs)
    for x in range(6):
        for y in range(6):
            for m in range(6):
                p[x][y] += Xp[x][m]*Xp[m][y]
    for x in range(6):
        for y in range(6):
            for m in range(6):
                mean[x][y] += (Xm[x][m]+Xm[m][y])*Xp[x][m]*Xp[m][y] / p[x][y]
                var[x][y] += (Xv[x][m] + Xv[m][y])*Xp[x][m]*Xp[m][y] / p[x][y]
    for x in range(6):
        for y in range(6):
            for m in range(6):
                var[x][y] += (Xm[x][m] + Xm[m][y] - mean[x][y])**2 *Xp[x][m]*Xp[m][y] / p[x][y]
    return mean, var, p

p = [float(raw_input()) for x in range(6)]
n = int(raw_input())
if n == 1:
    mean = 0
    var = 0
    for x in range(6):
        mean += p[x]*x
    for x in range(6):
        var += (x-mean)**2 *p[x]
else:
    probs = reduce_probs(p)
    Xm, Xv, Xp = calc_stats(n-1, probs)
    mean = 0
    var = 0
    for x in range(6):
        for y in range(6):
            mean += (x+Xm[x][y])*p[x]*Xp[x][y]
            var += Xv[x][y]*p[x]*Xp[x][y]
    for x in range(6):
        for y in range(6):
            var += (Xm[x][y]+x - mean)**2 * p[x]*Xp[x][y]
#print Xm, Xv, Xp
print '%.7f'%(mean + n)
print '%.7f'%(var,)
