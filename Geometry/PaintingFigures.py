#!/bin/python

from math import pi, acos, sqrt, atan2, hypot, cos, sin

O = 0., 0.

def add((a, b), (c, d)):
    return a + c, b + d

def sub((a, b), (c, d)):
    return a - c, b - d

def mul(c, (a, b)):
    return c*a, c*b

def mag((x, y)):
    return hypot(x, y)

def mag2(p):
    return mag(p)**2

def norm(p):
    return mul(1/mag(p), p)

def rot((x, y)):
    return y, -x

def dot((a, b), (c, d)):
    return a*c + b*d

def cross((a, b), (c, d)):
    return a * d - b * c

def bound(a, b, x):
    return float(max(a, min(b, x)))

def poly_area(poly):
    return sum(cross(poly[i-1], poly[i]) for i in xrange(len(poly)))

def ccw(poly):
    return poly if poly_area(poly) >= 0 else poly[::-1]

def angle((x, y)):
    return atan2(y, x) % (2*pi)

class Chip(object):
    def __init__(self, m):
        self.m = m
        self.events = []
        self.add(0., m)
        super(Chip, self).__init__()

    def add(self, a, b):
        self.change(a, b, +1)

    def subtract(self, a, b):
        self.change(a, b, -1)

    def change(self, a, b, s):
        assert 0 <= a <= b <= self.m
        self.events.append((a, +s))
        self.events.append((b, -s))

    def add_wrap(self, a, b):
        self.change_wrap(a, b, +1)

    def subtract_wrap(self, a, b):
        self.change_wrap(a, b, -1)

    def change_wrap(self, a, b, s):
        if a <= b:
            self.change(a, b, s)
        else:
            self.change(a, self.m, s)
            self.change(0, b, s)

    def segs(self):
        ct = 0
        prev = 0.
        for curr, d in sorted(self.events):
            if ct > 0:
                yield prev, curr
            ct += d
            prev = curr


def circ_intersect((C, R), (c, r)):
    # part of (C,R) inside (c,r)

    # to origin
    c = sub(c, C)

    # angle of other circle
    th = angle(c)
    x = mag(c)

    if abs(x) <= 1e-11:
        if R < r:
            return 0, 2*pi
        else:
            return 0, 0
    val = bound(-1, 1, (x*x + R*R - r*r) / (2*R*x))

    if val <= -1:
        return 0, 2*pi
    if val >= 1:
        return 0, 0
    TH = acos(val)
    a = (th - TH) % (2*pi)
    b = (th + TH) % (2*pi)
    return a, b

def _sector_fix(a, b):
    B = (b - a) % (2*pi)
    if B <= pi:
        return a, b, -1
    else:
        return b, a, +1

def circ_slice((c, r), (p, q)):
    # part of (c,r) inside (c,p,q). respect sign!
    p = sub(p, c)
    q = sub(q, c)

    ta, tb = _seg_slice(p, q, r)

    thp = angle(p)
    tha = angle(seg_point((p, q), ta))
    thb = angle(seg_point((p, q), tb))
    thq = angle(q)

    yield _sector_fix(thp, tha)
    yield _sector_fix(thb, thq)


def seg_slice((p, q), (c, r)):
    # part of seg (p,q) inside (c,r)
    p = sub(p, c)
    q = sub(q, c)
    return _seg_slice(p, q, r)

def _seg_slice(p, q, r):
    v = sub(q, p)

    A = mag2(v)
    B = dot(p, v)
    C = mag2(p) - r*r

    D = B*B - A*C
    if D <= 0:
        return 0, 0

    sqrtD = sqrt(D)
    ta = bound(0, 1, (-B - sqrtD) / A)
    tb = bound(0, 1, (-B + sqrtD) / A)

    return ta, tb

def circ_point((c, r), t):
    return add(c, mul(r, (cos(t), sin(t))))

def seg_point((p, q), a):
    # pa-p = a*(q-p)
    return add(p, mul(a, sub(q, p)))

def seg_intersect((p, q), (P, Q)):
    # (p + (q-p)t - P) x (Q - P) = 0
    return -cross(sub(p, P), sub(Q, P)) / cross(sub(q, p), sub(Q, P))

def proj_dir((p, q), x):
    q = sub(q, p)
    x = sub(x, p)
    return cross(x, q)

def proj_val((p, q), x):
    # index (param) of projection of x to (p,q)
    q = sub(q, p)
    x = sub(x, p)
    return bound(0, 1, dot(x, q) / mag2(q))

def union_area(circles, polys):
    # union of circles and poly

    area = 0.

    for i in xrange(len(circles)):
        ch = Chip(2*pi)

        # circles on circles
        for j in xrange(len(circles)):
            if j == i: continue
            a, b = circ_intersect(circles[i], circles[j])

            ch.subtract_wrap(a, b)

        # circles on polys
        for poly in polys:
            for j in xrange(len(poly)):
                p = poly[j-1]
                q = poly[j]

                for a, b, c in circ_slice(circles[i], (p, q)):
                    ch.change_wrap(a, b, c)


        c, r = circles[i]
        for a, b in ch.segs():
            pa = circ_point(circles[i], a)
            pb = circ_point(circles[i], b)

            area += (b - a) * r**2
            area -= poly_area([c, pa, pb])
            area += poly_area([O, pa, pb])

    for I in xrange(len(polys)):
        for i in xrange(len(polys[I])):
            p = polys[I][i-1]
            q = polys[I][i]
            # polys on circles
            ch = Chip(1.)
            for circ in circles:
                a, b = seg_slice((p, q), circ)
                ch.subtract(a, b)

            # polys on polys
            for J in xrange(len(polys)):
                if J == I: continue
                P = polys[J][-1]
                A = proj_dir((p, q), P)
                for j in xrange(len(polys[J])):
                    Q = polys[J][j]
                    B = proj_dir((p, q), Q)
                    if A > 0 and B > 0:
                        a = proj_val((p, q), P)
                        b = proj_val((p, q), Q)
                    elif A > 0:
                        a = proj_val((p, q), P)
                        b = bound(0, 1, seg_intersect((p, q), (P, Q)))
                    elif B > 0:
                        a = bound(0, 1, seg_intersect((p, q), (P, Q)))
                        b = proj_val((p, q), Q)
                    else:
                        a = b = 0.

                    if a <= b:
                        ch.subtract(a, b)
                    else:
                        ch.add(b, a)

                    P = Q
                    A = B

            for a, b in ch.segs():
                pa = seg_point((p, q), a)
                pb = seg_point((p, q), b)
                area += poly_area([O, pa, pb])

    return area

circles = set()
polys = set()

for i in xrange(input()):
    x1, y1, x2, y2, r = map(float, raw_input().strip().split())
    p1 = x1, y1
    p2 = x2, y2
    circles.add((p1, r))
    circles.add((p2, r))
    v = mul(r, norm(rot(sub(p2, p1))))
    polys.add(tuple(ccw([add(p1, v), sub(p1, v), sub(p2, v), add(p2, v)])))

# perturb
from random import random, seed
seed(1111)

def rd():
    return (random() - 0.5) * 5e-13

def perturb_point(p):
    return add(p, (rd(), rd()))

def perturb_circ((p, r)):
    return perturb_point(p), r

def perturb_poly(p):
    return map(perturb_point, p)

circles = [perturb_circ(c) for c in circles]
polys = [perturb_poly(p) for p in polys]

print 0.5 * union_area(circles, polys)
