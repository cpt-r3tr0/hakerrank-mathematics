#include<stdio.h>

#define div(a,b) mul(a, recip(b))
#define ll long long
#define nonzero(c) (c.x || c.y)
#define p 1000000007
#define fix(f) (f.n * inv(f.d) % p)

ll x, y;
void egcd(ll a, ll b) {
    if (!b) {
        x = 1; y = 0;
    } else {
        egcd(b, a % b);
        ll t = x - (a / b) * y;
        x = y;y = t;
    }
}

ll inv(ll a) {egcd(a, p);return x % p;}

struct COMPLEX {ll x, y;};

COMPLEX complex(ll x = 0, ll y = 0) { COMPLEX c;c.x = x;c.y = y;return c;}

COMPLEX recip(COMPLEX a) {
    COMPLEX c;ll r = inv((a.x * a.x + a.y * a.y) % p);
    c.x = a.x * r % p; c.y = -a.y * r % p;
    return c;
}

COMPLEX add(COMPLEX a, COMPLEX b) {COMPLEX c;c.x = (a.x + b.x) % p; c.y = (a.y + b.y) % p; return c;}

COMPLEX mul(COMPLEX a, COMPLEX b) {COMPLEX c;c.x = (a.x * b.x - a.y * b.y) % p;c.y = (a.x * b.y + a.y * b.x) % p;return c;}

COMPLEX neg(COMPLEX a) { COMPLEX c;c.x = -a.x;c.y = -a.y;return c;}

COMPLEX conj(COMPLEX a) {    COMPLEX c; c.x = a.x;c.y = -a.y; return c;}

COMPLEX ra, rb, rc, rd;


void omul(COMPLEX fa, COMPLEX fb, COMPLEX fc, COMPLEX fd, COMPLEX ga, COMPLEX gb, COMPLEX gc, COMPLEX gd) {
    ra.x = (fa.x * ga.x - fa.y * ga.y + fb.x * gc.x - fb.y * gc.y) % p;
    ra.y = (fa.x * ga.y + fa.y * ga.x + fb.x * gc.y + fb.y * gc.x) % p;
    rb.x = (fa.x * gb.x - fa.y * gb.y + fb.x * gd.x - fb.y * gd.y) % p;
    rb.y = (fa.x * gb.y + fa.y * gb.x + fb.x * gd.y + fb.y * gd.x) % p;
    rc.x = (fc.x * ga.x - fc.y * ga.y + fd.x * gc.x - fd.y * gc.y) % p;
    rc.y = (fc.x * ga.y + fc.y * ga.x + fd.x * gc.y + fd.y * gc.x) % p;
    rd.x = (fc.x * gb.x - fc.y * gb.y + fd.x * gd.x - fd.y * gd.y) % p;
    rd.y = (fc.x * gb.y + fc.y * gb.x + fd.x * gd.y + fd.y * gd.x) % p;
}


void opow(COMPLEX a, COMPLEX b, COMPLEX c, COMPLEX d, ll e) {
    if (e == 1 || !nonzero(b) && !nonzero(c) && a.x == d.x && a.y == d.y) {
        ra = a;rb = b;
        rc = c;rd = d;
    } else if (e & 1) {
        opow(a, b, c, d, e - 1);
        omul(ra, rb, rc, rd, a, b, c, d);
    } else {
        omul(a, b, c, d, a, b, c, d);
        opow(ra, rb, rc, rd, e >> 1);
    }
}

struct FRACTION { ll n, d;};

COMPLEX ZERO = complex();
COMPLEX ONE = complex(1);

char s[11];
int main() {
    int z;scanf("%d", &z);
    for (int cas = 1; cas <= z; cas++) {
        int n;
        ll k;
        FRACTION tx, ty, ta, tb, tc;
        COMPLEX c;
        scanf("%d %lld %lld/%lld %lld/%lld", &n, &k, &tx.n, &tx.d, &ty.n, &ty.d);
        COMPLEX fa = ONE;COMPLEX fb = ZERO;
        COMPLEX fc = ZERO;COMPLEX fd = ONE;
        int has_conj = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            if (*s == 'S') {
                scanf("%lld/%lld", &tc.n, &tc.d);
                c = complex(fix(tc));
                fa = mul(fa, c);
                fb = mul(fb, c);
            } else if (*s == 'T') {
                scanf("%lld/%lld %lld/%lld", &ta.n, &ta.d, &tb.n, &tb.d);
                COMPLEX c = complex(fix(ta), fix(tb));
                fa = add(fa, mul(fc, c));
                fb = add(fb, mul(fd, c));
            } else if (*s == 'R') {
                scanf("%lld/%lld %lld/%lld", &ta.n, &ta.d, &tb.n, &tb.d);
                tb.n = -tb.n;
                COMPLEX c = complex(fix(ta), fix(tb));
                fa = mul(fa, c);
                fb = mul(fb, c);
            } else if (*s == 'F') {
                scanf("%s", s);
                if (*s == 'Y') {
                    fa.x = -fa.x;
                    fb.x = -fb.x;
                    fc.y = -fc.y;
                    fd.y = -fd.y;
                    has_conj = !has_conj;
                } else {
                    fa.y = -fa.y;
                    fb.y = -fb.y;
                    fc.y = -fc.y;
                    fd.y = -fd.y;
                    has_conj = !has_conj;
                }
            } else {
                COMPLEX ft;
                ft = fc; fc = fa; fa = ft;
                ft = fd; fd = fb; fb = ft;
                fa.y = -fa.y;
                fb.y = -fb.y;
                fc.y = -fc.y;
                fd.y = -fd.y;
                has_conj = !has_conj;
            }
        }

        COMPLEX z = complex(fix(tx), fix(ty));
        int inf = 0;
        if (has_conj) {
            if (k & 1) {
                z.y = -z.y;
                COMPLEX D = add(mul(fc, z), fd);
                if (nonzero(D)) {
                    COMPLEX N = add(mul(fa, z), fb);
                    z = div(N, D);
                } else inf = 1;
            }
            k >>= 1;
            omul(fa, fb, fc, fd, conj(fa), conj(fb), conj(fc), conj(fd));
            fa = ra; fb = rb;fc = rc; fd = rd;
        }
        if (k) {
            opow(fa, fb, fc, fd, k);
            if (inf) {
                if (nonzero(rc)) {
                    z = div(ra, rc);
                    inf = 0;
                }
            } else {
                COMPLEX D = add(mul(rc, z), rd);
                if (nonzero(D)) {
                    COMPLEX N = add(mul(ra, z), rb);
                    z = div(N, D);
                } else  inf = 1;
            }
        }

        if (inf) printf("WONDERLAND\n");
        else {
            ll x = z.x % p;ll y = z.y % p;
            if (x < 0) x += p;if (y < 0) y += p;
            printf("%lld %lld\n", x, y);
        }
    }
}
