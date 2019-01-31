# Enter your code here. Read input from STDIN. Print output to STDOUT

from collections import namedtuple
from bisect import bisect
from sys import stderr

line = namedtuple('line', 'm,b,i')
node = namedtuple('node', 'lo, hi, mid, hull, left, right')
hull = namedtuple('hull', 'lines, sep')

def main():
    nlines, = readints()
    lines = [readints() for _ in range(nlines)]
    nreqs, = readints()
    reqs = [readints() for _ in range(nreqs)]
    assert all(len(line)==2 for line in lines)
    assert all(len(req)==4 for req in reqs)
    segtree = getsegtree(lines)
#    print(segtree, file=stderr)
    for req in reqs:
#        print(req, file=stderr)
        print('YES' if below(segtree, *req) else 'NO')

def readints():
    return [int(f) for f in input().split()]

def getsegtree(lines):
    lines = [line(m, b, i) for i, (m, b) in enumerate(lines)]
    return treenode(0, len(lines)-1, lines)

def treenode(lo, hi, lines):
#    assert len(lines) == hi - lo + 1
    if lo == hi:
        return node(lo, hi, lo, gethull(lines[lo:hi+1]), None, None)
    mid = (lo + hi)//2
    left, right = treenode(lo, mid, lines), treenode(mid+1, hi, lines)
    return node(lo, hi, mid, gethull(left.hull.lines + right.hull.lines), left, right)

def below(segtree, lo, hi, x, y):
#    return below0(segtree, lo-1, hi-1, x, y)
    lo, hi = lo - 1, hi - 1
    while True:
        if hi <= segtree.mid:
            if segtree.left is None:
                return hullbelow(segtree.hull, x, y)
            segtree = segtree.left
        elif lo > segtree.mid:
            segtree = segtree.right
        else:
            break
    if lo == segtree.lo and hi == segtree.hi:
        return hullbelow(segtree.hull, x, y)
    ltree = segtree.left
    while True:
        if lo <= ltree.lo:
            if hullbelow(ltree.hull, x, y):
                return True
            else:
                break
        elif lo <= ltree.mid:
            if hullbelow(ltree.right.hull, x, y):
                return True
            ltree = ltree.left
        else:
            ltree = ltree.right
    rtree = segtree.right
    while True:
        if rtree.hi <= hi:
            return hullbelow(rtree.hull, x, y)
        elif rtree.mid < hi:
            if hullbelow(rtree.left.hull, x, y):
                return True
            rtree = rtree.right
        else:
            rtree = rtree.left
    return False

def below0(segtree, lo, hi, x, y):
    if lo <= segtree.lo and segtree.hi <= hi:
        return hullbelow(segtree.hull, x, y)
    if hi <= segtree.mid:
        return below0(segtree.left, lo, hi, x, y)
    if segtree.mid < lo:
        return below0(segtree.right, lo, hi, x, y)
    return below0(segtree.left, lo, hi, x, y) or below0(segtree.right, lo, hi, x, y)

def gethull(lines):
    lines.sort()
    sep = []
    uselines = [lines[0]]
    for line in lines[1:]:
        if line.m == uselines[-1].m:
            if sep:
                sep.pop()
                uselines.pop()
            else:
                uselines[0] = line
                continue
        while True:
            inter = -((line.b - uselines[-1].b)//(line.m - uselines[-1].m))
            if len(sep) == 0 or inter > sep[-1]:
                sep.append(inter)
                uselines.append(line)
                break
            sep.pop()
            uselines.pop()
    return hull(sep=sep, lines=uselines)

def hullbelow(hull, x, y):
#    print(x, y, hull, file=stderr)
    line = hull.lines[bisect(hull.sep, x)]
    return y < line.m * x + line.b

main()
