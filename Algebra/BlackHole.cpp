#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define forit(it,v) for (__typeof(v.begin()) it = v.begin(); it != v.end(); ++it)
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
ll n, bb;
int mod, a, b, bpn;
int C[800][800];
int ans[800], oans[800];

int modPow(ll a, ll n) {
    a %= mod;
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
    return res;
}

void Calc(ll n) {

    if (n == 0) {
        memset(ans, 0, sizeof(ans));
        ans[0] = 1 % mod;
        bpn = 1 % mod;
        return;
    }

    if (n % 2 == 0) {

        Calc(n - 1);
        bpn = (1ll * bpn * b) % mod;

        int np = 1;
        n %= mod;
        for (int i = 0; i <= a; ++i) {
            ans[i] = (ans[i] + 1ll * np * bpn) % mod;
            np = (1ll * np * n) % mod;
        }
        return;
    }

    ll m = (n + 1) / 2;
    Calc(m - 1);

    memcpy(oans, ans, sizeof(int) * (a + 1));
    int bpm = (1ll * bpn * b) % mod;
    bpn = (1ll * bpm * bpn) % mod;

    m %= mod;
    for (int i = 0; i <= a; ++i) {
        int pm = 1;
        for (int j = i; j >= 0; --j) {

            int now = (1ll * C[i][j] * pm) % mod;
            now = (1ll * now * oans[j]) % mod;
            now = (1ll * now * bpm) % mod;
            pm = (pm * m) % mod;
            ans[i] = (ans[i] + now) % mod;
        }
    }
}
void Solve() {
    scanf("%lld%d%lld%d", &n, &a, &bb, &mod);
    b = bb % mod;
    if (b < 0) b += mod;

    for (int i = 0; i <= a; ++i) {
        C[i][0] = 1 % mod;
        for (int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;

    }
    Calc(n);
    printf("%d\n", ans[a]);
}

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests--)
        Solve();
    return 0;
}
