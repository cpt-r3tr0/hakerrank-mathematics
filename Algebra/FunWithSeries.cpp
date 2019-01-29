#include <iostream>

#include <cassert>

using namespace std;

#define ll long long
#define MOD 1000000007

int fib[1000005];
int inv[1000005];

int cnt[3][1005];

ll modpow(ll a, ll b, ll mod) {
    ll r = 1;

    a %= mod;

    while (b) {
        if (b & 1) {
            r = (r * a) % mod;
        }

        a = (a * a) % mod;
        b >>= 1;
    }

    return r;
}

void fibo(ll a, ll b) {
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i < 1000005; i++) {
        fib[i] = ((a * fib[i - 1]) % MOD + (b * fib[i - 2]) % MOD) % MOD;
    }

    fib[0] = 1;
    inv[0] = 1;

    for (int i = 1; i < 1000005; i++) {
        fib[i] = (1LL * fib[i] * fib[i - 1]) % MOD;
        inv[i] = modpow(fib[i], MOD - 2, MOD);
    }
}

void pre(ll b) {
    for (int i = 1; i < 1004; i++) {
        int s = fib[i + 1];

        int s1 = 0;
        int s2 = 0;

        for (int j = 0; j <= (i + 1) / 2; j++) {
            int q = (1LL * inv[j] * inv[i + 1 - j]) % MOD;
            int r = (1LL * q * modpow(b, 1LL * j * (j - 1) / 2, MOD)) % MOD;

            if (j % 4 == 1 or j % 4 == 2) {
                s2 = (s2 + r) % MOD;
            } else {
                s1 = (s1 + r) % MOD;
            }

            int k = (i + 1 - j);

            if (k != j) {
                ll r = (1LL * q * modpow(b, 1LL * k * (k - 1) / 2, MOD)) % MOD;

                if (k % 4 == 1 or k % 4 == 2) {
                    s2 = (s2 + r) % MOD;
                } else {
                    s1 = (s1 + r) % MOD;
                }
            }
        }

        s1 = (1LL * s1 * s) % MOD;
        s2 = (1LL * s2 * s) % MOD;

        if (s1 > s2) {
            cnt[0][i] = 1;
        } else if (s1 < s2) {
            cnt[1][i] = 1;
        } else {
            cnt[2][i] = 1;
        }
    }

    for (int i = 1; i < 1001; i++) {
        for (int j = 0; j < 3; j++) {
            cnt[j][i] += cnt[j][i - 1];
        }
    }
}

int main()
{
    int a, b, q;
    cin >> a >> b >> q;
    assert(a >= 1 and a <= 1e6);
    assert(b >= 1 and b <= 1e6);
    assert(q >= 1 and q <= 5e4);

    fibo(a, b);
    pre(b);

    while (q--) {
        int t;
        cin >> t;
        assert(t >= 1 and t <= 2);

        if (t == 1) {
            int l, r;
            cin >> l >> r;
            assert(l >= 1 and l <= 1e3);
            assert(r >= l and r <= 1e3);

            int count1 = cnt[0][r] - cnt[0][l - 1];
            int count2 = cnt[1][r] - cnt[1][l - 1];
            int count3 = cnt[2][r] - cnt[2][l - 1];

            cout << count1 << " " << count2 << " " << count3 << endl;
        } else {
            int p, u, v;
            cin >> p >> u >> v;
            assert(p >= 1 and p <= 1e6);
            assert(u >= 2 and u <= p + 1);
            assert(v >= u and v <= p + 1);

            int phi = u + v - p - 2;

            if (phi < 0) {
                phi = -phi;
            }

            cout << modpow((1LL * fib[v] * modpow(fib[u - 1], MOD - 2, MOD)) % MOD, ((1LL * phi * (v - u + 1)) % (MOD - 1) + modpow(b, 1LL * p * (p + 1) * (p + 2) / 6, MOD - 1)) % (MOD - 1), MOD) << endl;
        }
    }

    return 0;
}
