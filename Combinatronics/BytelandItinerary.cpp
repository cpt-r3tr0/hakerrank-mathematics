#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 3e5 + 100;
const int M = 1e9 + 7;

int n, m, k;

inline int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = (1ll * res * a) % M;
        }
        a = (1ll * a * a) % M;
    }
    return res;
}

inline int inv(int x) {
    return power(x, M - 2);
}

int fact[N], ifact[N];

inline void precalc() {
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (1ll * fact[i - 1] * i) % M;
        ifact[i] = (1ll * ifact[i - 1] * inv(i)) % M;
    }
}

inline int cnk(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    int cur1 = (1ll * fact[n] * ifact[k]) % M;
    return (1ll * cur1 * ifact[n - k]) % M;
}

int main() {
    precalc();
    cin >> n >> m >> k;
    k = k * 2 / m;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * i <= n - 1; j++) {
            int cur1 = (1ll * power(m, n - j * i) * power(m - k, j)) % M;
            int cur2 = (1ll * cur1 * power(k, j * (i - 1))) % M;
            int cur3 = (1ll * cur2 * cnk(n - j * (i - 1) - 1, j)) % M;
            if (j & 1) {
                if ((ans += cur3) >= M) {
                    ans -= M;
                }
            } else {
                if ((ans -= cur3) < 0) {
                    ans += M;
                }
            }
        }
        for (int j = 0; j * i <= n - i; j++) {
            int cur1 = (1ll * power(m, n - (j + 1) * i + 1) * power(m - k, j)) % M;
            int cur2 = (1ll * cur1 * power(k, (j + 1) * (i - 1))) % M;
            int cur3 = (1ll * cur2 * cnk(n - j * (i - 1) - i, j)) % M;
            if (j & 1) {
                if ((ans -= cur3) < 0) {
                    ans += M;
                }
            } else {
                if ((ans += cur3) >= M) {
                    ans -= M;
                }
            }
        }
    }
    cout << (1ll * ans * inv(power(m, n))) % M << endl;
    return 0;
}
