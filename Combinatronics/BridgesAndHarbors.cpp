#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;
typedef long long L;
typedef pair<int,int> PII;
typedef pair<L,L> PLL;

L pw(L n, L e) {
    L res = 1;
    while (e--) res *= n;
    return res;
}

L pw(L n, L e, L MOD) {
    L res = 1;
    while (e) {
        if (e & 1)
            res = res * n % MOD;
        if (e >>= 1)
            n = n * n % MOD;
    }
    return res;
}

L gcd(L a, L b) {
    return b ? gcd(b, a%b) : a;
}

L gcd2(L MOD, L n) {
    if (!n) return 0;
    L g = gcd(MOD, n);
    L res = 1;
    while (g > 1) {
        res *= g;
        n /= g;
        g = gcd(MOD, n);
    }
    return res;
}

PLL egcd(L a, L b) {
    if (!b) return PLL(1,0);
    L q = a/b;
    L r = a-b*q;
    PLL st = egcd(b,r);
    return PLL(st.second, st.first-q*st.second);
}

L modinv(L x, L p) {
    return egcd(p,x).second;
}

L solve() {
    L n,m,K,MOD;
    cin >> n >> m >> K >> MOD;
    if (MOD == 1) return 0;
    if (n==m) return 1;
    vector<int> G;
    for (int i = 0; i <= m*K; i++)
        G.push_back(gcd2(MOD, i));
    vector<int> d, b;
    d.push_back(1);
    for (L i = 1; i <= m; i++) {
        swap(b, d);
        d.clear();
        d.push_back(1);
        L C = 1, D = 1;
        for (int j = 0; j < i*K; j++) {
            if (j >= K) {
                d.push_back((d[j] - b[j-K] * C % MOD * (D % MOD)) % MOD * i % MOD);
                int g1 = G[j+1], g2 = G[j-K+1];
                C = C * ((j+1)/g1) % MOD * modinv((j-K+1)/g2, MOD) % MOD;
                D = D * g1 / g2;
            } else {
                d.push_back(i * d[j] % MOD);
            }
        }
    }
    L res = d[1] * pw(n-m, n-m-1, MOD) % MOD;
    L C = 1, D = 1;
    for (int Q = 2; Q <= m*K && Q <= n-m; Q++) {
        int g1 = gcd2(MOD, n-m-Q+1), g2 = G[Q-1];
        C = C * ((n-m-Q+1)/g1) % MOD * modinv((Q-1)/g2, MOD) % MOD;
        D = D * g1 / g2;
        res += C * (D % MOD) % MOD * pw(n-m, n-m-Q, MOD) % MOD * d[Q] % MOD;
    }
    res %= MOD;
    C = 1; D = 1;
    for (int Q = 1; Q <= m; Q++) {
        int g1 = gcd2(MOD, n+1-Q), g2 = G[Q];
        C = C * ((n+1-Q)/g1) % MOD * modinv(Q/g2, MOD) % MOD;
        D = D * g1 / g2;
    }
    res = res * C % MOD * (D % MOD) % MOD;
    return (res + MOD) % MOD;
}

int main() {
    int T;
    cin >> T;
    while (T--) cout << solve() << endl;
}
