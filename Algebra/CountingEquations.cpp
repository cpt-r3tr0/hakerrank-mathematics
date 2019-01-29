#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <ctime>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<PII, int> PI3;
typedef pair<PI3, vector<int> > PIV;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define mp3(x, y, z) mp(mp(x, y), z)
#define fi3 fi.fi
#define se3 fi.se
#define th3 se
#define pct __builtin_popcount
#define ctz __builtin_ctz

#define P 1000000007
#define N 1010

int n, m, p, S0, wn;
vector<PII> w;
int px[N], py[N], qx[N], qy[N];
int sx[N], sy[N];
int p0[N]; int mn, mm;

bool cmpx(int x, int y) { return sx[x] > sx[y]; }
bool cmpy(int x, int y) { return sy[x] > sy[y]; }

int F0[2010][1010];
map<PIV, int> F1;

int rem(int x, int w) {
    return (x >> w+1 << w) + (x & ((1 << w)-1));
}

int rem(int x, int w1, int w2) {
    if (w1 > w2) swap(w1, w2);
    return rem(rem(x, w1), w2-1);
}

int gg(int n, int m, vector<int> a, int r) {
    if (r < 0 || r > n || r > m) return 0;
    if (r == 0 || n == 0 || m == 0) return 1;

    PIV wp = mp(mp3(n, m, r), a);
    if (F1.find(wp) != F1.end()) return F1[wp];
    int &S = F1[wp];

    for (int j = 2; j >= 0; j --) {
        for (int i = n-1; i >= 0; i --)
            if (pct(a[i]) <= j || pct(a[i]) >= m-j) {
                swap(a[i], a[n-1]);
                break;
            }
    }

    int pc = pct(a[n-1]);
    if (pc == m) {
        vector<int> a1;
        for (int i = 0; i < n-1; i ++) a1.pb(a[i]);
        S = gg(n-1, m, a1, r);
    } else
        if (pc == 0) {
            vector<int> a1;
            for (int i = 0; i < n-1; i ++) a1.pb(a[i]);
            int S1 = gg(n-1, m, a1, r);
            int S2 = gg(n-1, m, a1, r-1);
            (S += (ll)p0[r]*S1%P) %= P;
            (S += (ll)(p0[m]-p0[r-1]+P)%P*S2%P) %= P;
        } else
            if (pc == m-1) {
                vector<int> a1;
                for (int i = 0; i < n-1; i ++) a1.pb(a[i]);
                (S += gg(n-1, m, a1, r)) %= P;
                int inva = (1 << m) - 1 - a[n-1];
                int w = ctz(inva), s = 0;
                for (int i = 0; i < n-1; i ++) {
                    if (~(a1[i] >> w)&1) s ++;
                    a1[i] = rem(a1[i], w);
                }
                (S += (ll)(p-1)*p0[s]%P*gg(n-1, m-1, a1, r-1)%P) %= P;
            } else
                if (pc == 1) {
                    vector<int> a1, a2;
                    for (int i = 0; i < n-1; i ++) a1.pb(a[i]);
                    int w = ctz(a[n-1]);
                    for (int i = 0; i < n-1; i ++)
                        a2.pb(rem(a[i], w));
                    int S1 = gg(n-1, m-1, a2, r);
                    int S2 = gg(n-1, m-1, a2, r-1);
                    int S3 = (gg(n-1, m, a1, r)-S1+P)%P;
                    int S4 = (gg(n-1, m, a1, r-1)-S2+P)%P;
                    (S += (ll)p0[r]*S1%P) %= P;
                    (S += (ll)(p0[m-1]-p0[r-1]+P)%P*S2%P) %= P;
                    (S += (ll)p0[r-1]*S3%P) %= P;
                    if (r >= 2) (S += (ll)(p0[m-1]-p0[r-2]+P)%P*S4%P) %= P;
                } else
                    if (pc == m-2) {
                        vector<int> a1;
                        for (int i = 0; i < n-1; i ++) a1.pb(a[i]);
                        (S += gg(n-1, m, a1, r)) %= P;
                        int inva = (1 << m) - 1 - a[n-1];
                        int w1 = ctz(inva), w2 = ctz(inva^(1 << w1));
                        int s1 = 0, s2 = 0;
                        for (int i = 0; i < n-1; i ++) {
                            if (~(a[i] >> w1) & 1) s1 ++;
                            if (~(a[i] >> w2) & 1) s2 ++;
                        }

                        for (int i = 0; i < n-1; i ++)
                            a1[i] = rem(a[i], w1);
                        (S += (ll)(p-1)*p0[s1]%P*gg(n-1, m-1, a1, r-1)%P) %= P;
                        for (int i = 0; i < n-1; i ++)
                            a1[i] = rem(a[i], w2);
                        (S += (ll)(p-1)*p0[s2]%P*gg(n-1, m-1, a1, r-1)%P) %= P;

                        int s3 = 0;
                        vector<int> a2;
                        for (int i = 0; i < n-1; i ++) {
                            if ((~(a[i] >> w1) & 1) && (~(a[i] >> w2) &1)) s3 ++;
                            int x = a[i];
                            if (~(x >> w1)&1)
                                if ((x >> w2) & 1) x ^= (1 << w2);
                            a2.pb(rem(x, w1));
                        }
                        (S += (ll)(p-1)*(p-1)%P*p0[s3]%P*gg(n-1, m-1, a2, r-1)%P) %= P;
                    } else
                        if (pc == 2) {
                            int w1 = ctz(a[n-1]), w2 = ctz(a[n-1] ^ (1 << w1));
                            vector<int> a0, a1, a2, a3, a4;
                            for (int i = 0; i < n-1; i ++)
                                a0.pb(rem(a[i], w1, w2));
                            int S1 = gg(n-1, m-2, a0, r);
                            int S2 = gg(n-1, m-2, a0, r-1);
                            (S += (ll)p0[r]*S1%P) %= P;
                            (S += (ll)(p0[m-2]-p0[r-1]+P)%P*S2%P) %= P;

                            for (int i = 0; i < n-1; i ++) {
                                a1.pb(rem(a[i], w1));
                                a2.pb(rem(a[i], w2));
                            }
                            int S3 = (gg(n-1, m-1, a1, r)-S1+P)%P;
                            int S4 = (gg(n-1, m-1, a1, r-1)-S2+P)%P;
                            int S5 = (gg(n-1, m-1, a2, r)-S1+P)%P;
                            int S6 = (gg(n-1, m-1, a2, r-1)-S2+P)%P;
                            (S += (ll)p0[r-1]*S3%P) %= P;
                            if (r >= 2) (S += (ll)(p0[m-2]-p0[r-2]+P)%P*S4%P) %= P;
                            (S += (ll)p0[r-1]*S5%P) %= P;
                            if (r >= 2) (S += (ll)(p0[m-2]-p0[r-2]+P)%P*S6%P) %= P;

                            for (int i = 0; i < n-1; i ++) {
                                int x = a[i];
                                if ((x >> w1) &1) x |= (1 << w2);
                                a3.pb(rem(x, w1));
                            }
                            int S7 = (ll)(p-1)*(gg(n-1, m-1, a3, r)-S1+P)%P;
                            int S8 = (ll)(p-1)*(gg(n-1, m-1, a3, r-1)-S2+P)%P;
                            (S += (ll)p0[r-1]*S7%P) %= P;
                            if (r >= 2)(S += (ll)(p0[m-2]-p0[r-2]+P)%P*S8%P) %= P;

                            for (int i = 0; i < n-1; i ++) a4.pb(a[i]);
                            int S9 = (gg(n-1, m, a4, r)-((ll)S1+S3+S5+S7)%P+P)%P;
                            int S10 = (gg(n-1, m, a4, r-1)-((ll)S2+S4+S6+S8)%P+P)%P;
                            if (r >= 2) (S += (ll)p0[r-2]*S9%P) %= P;
                            if (r >= 3) (S += (ll)(p0[m-2]-p0[r-3]+P)%P*S10%P) %= P;
                        } else {
                            vector<int> b;
                            for (int i = 0; i < m; i ++) b.pb(0);
                            for (int i = 0; i < n; i ++)
                                for (int j = 0; j < m; j ++)
                                    if ((a[i] >> j)&1) b[j] |= (1 << i);
                            S = gg(m, n, b, r);
                        }
    return S;
}

int ff(int n, int m, int r) {
    if (r < 0 || r > n || r > m) return 0;
    if (r == 0 || n == 0 || m == 0) return 1;
    if (F0[n+m][r] != -1) return F0[n+m][r];
    int &S = F0[n+m][r] = 0;
    if (n > mn) {
        (S += (ll)p0[r]*ff(n-1, m, r)%P) %= P;
        (S += (ll)(p0[m]-p0[r-1]+P)%P*ff(n-1, m, r-1)%P) %= P;
    } else
        if (m > mm) {
            (S += (ll)p0[r]*ff(n, m-1, r)%P) %= P;
            (S += (ll)(p0[n]-p0[r-1]+P)%P*ff(n, m-1, r-1)%P) %= P;
        } else {
            vector<int> a;
            for (int i = 0; i < n; i ++) a.pb(0);
            for (int i = 0; i < wn; i ++)
                a[w[i].fi] |= (1 << w[i].se);
            S = gg(n, m, a, r);
        }
    return S;
}

void solve() {
    static int _ = 0; _ ++;
    memset(F0, -1, sizeof F0);
    F1.clear();

    p0[0] = 1;
    for (int i = 1; i < N; i ++)
        p0[i] = (ll)p0[i-1]*p%P;

    memset(sx, 0, sizeof sx);
    memset(sy, 0, sizeof sy);
    w.clear();
    for (int i = 0; i < wn; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x, --y;
        w.pb(mp(x, y));
        sx[x] ++; sy[y] ++;
    }

    for (int i = 0; i < n; i ++) px[i] = i;
    for (int i = 0; i < m; i ++) py[i] = i;
    sort(px, px+n, cmpx);
    sort(py, py+m, cmpy);

    for (int i = 0; i < n; i ++) qx[px[i]] = i;
    for (int i = 0; i < m; i ++) qy[py[i]] = i;
    for (int i = 0; i < wn; i ++)
        w[i] = mp(qx[w[i].fi], qy[w[i].se]);
    for (int i = 0; i < wn; i ++) {
        mn = max(mn, w[i].fi + 1);
        mm = max(mm, w[i].se + 1);
    }

    int S = 0;
    for (int i = 0; i <= min(n, m); i ++)
        if (S0 == 0) {
            (S += (ll)(p0[n]-p0[i]+P)%P*ff(n, m, i)%P) %= P;
        } else
            if (p0[m-i] == S0) {
                (S += (ll)p0[i]*ff(n, m, i)%P) %= P;
            }
    printf ("Case #%d: %d\n", _, S);
}

int main() {
    int _ = 0;
    int test;
    scanf("%d", &test);
    while (scanf("%d%d%d%d%d", &n, &m, &p, &S0, &wn) != EOF) {
        solve();
    }
    return 0;
}
