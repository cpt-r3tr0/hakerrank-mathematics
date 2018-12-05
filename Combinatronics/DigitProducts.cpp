#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define rep(i,n) rep2(i,0,n)
#define rep2(i,m,n) for(int i=m;i<(n);i++)
#define ALL(c) (c).begin(),(c).end()

const ll MOD = 1000000007;

ll comb[110][110];
ll dp[110][120][120];

ll calc(int len, ll k)
{
    if (len == 0) return (k == 1);

    int c5 = 0, c7 = 0, c2 = 0, c3 = 0;
    while (k % 5 == 0) {
    ++c5;
    k /= 5;
    --len;
    }

    while (k % 7 == 0) {
    ++c7;
    k /= 7;
    --len;
    }

    while (k % 2 == 0) {
    ++c2;
    k /= 2;
    }

    while (k % 3 == 0) {
    ++c3;
    k /= 3;
    }

    if (len < 0 || k != 1) return 0;
    ll res = dp[len][c2][c3];
    len += c5 + c7;
    res = res * comb[len][c5] % MOD * comb[len-c5][c7] % MOD;
    return res;
}

void add(ll &x, ll y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

ll acc(string s, ll k) // count x < s
{
    int len = s.size();
    ll res = 0;
    ll cur = 1;

    for (int i = 1; i < len; ++i) add(res, calc(i, k));

    rep(i, len) {
      int x = s[i] - '0';

      for (int j = 1; j < x; ++j) {
          ll nc = cur * j;
          if (k % nc == 0) add(res, calc(len-i-1, k / nc));
        }

        cur *= x;
        if (x == 0 || k % cur != 0) break;
    }
    return res;
}

int same(string s, ll k) {
    ll t = 1;

    rep(i, s.size()) {
    int x = s[i] - '0';
    if (t * x > k) return false;
    t *= x;
    }

    return t == k;
}

int TC;
ll x, k;
string a, b;

int main() {
    comb[0][0] = 1;
    for (int i = 1; i < 110; ++i) {
    comb[i][0] = comb[i][i] = 1;
    for (int j = 1; j < i; ++j)
        comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
    }

    dp[0][0][0] = 1;

    rep(i, 105) {
        rep(j, 110) {
            rep(k, 110) {
              add(dp[i+1][j][k], dp[i][j][k]);
              add(dp[i+1][j+1][k], dp[i][j][k]);
              add(dp[i+1][j][k+1], dp[i][j][k]);
              add(dp[i+1][j+2][k], dp[i][j][k]);
              add(dp[i+1][j+1][k+1], dp[i][j][k]);
              add(dp[i+1][j+3][k], dp[i][j][k]);
              add(dp[i+1][j][k+2], dp[i][j][k]);
            }
        }
    }
    cin >> TC;

    rep(tc, TC) {
      cout << "Case " << tc + 1 << ": ";
      cin >> a >> b >> k;
      cout << (acc(b, k) - acc(a, k) + same(b, k) + MOD) % MOD << '\n';
    }
    return 0;
}
