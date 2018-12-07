#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <iomanip>
#include <map>
#include <complex>
#include <set>


using namespace std;
typedef long long LL;
typedef pair <int, int> PII;

const int N = 2e5 + 10;
const LL mod = 1000000007;


LL fct[2 * N], cat[2 * N], dp[222][222], cat1[2 * N];

LL modpw(LL x, LL exp1) {
  if(exp1 == 0)
    return 1;
  LL y = modpw(x, exp1 / 2);
  y = (y * y) % mod;
  if(exp1 & 1) {
    y = (y * x) % mod;
  }
  return y;
}

LL ncr(LL n, LL r) {
  if(r > n)
    return 0;
  if(n == r)
    return 1;
  LL f = (fct[r] * fct[n - r]) % mod;
  LL res = (fct[n] * modpw(f, mod - 2)) % mod;
  return res;
}


void pre() {
  fct[0] = cat[0] = cat1[0] = 1;
  for(int i = 1; i < N; i++)
    fct[i] = (fct[i - 1] * i) % mod;

  for(int i = 1; i < N; i++) {
    cat[i] = (ncr(2 * i, i) * modpw(i + 1, mod - 2)) % mod;
    cat1[i] = cat[i];
  }
  for(int i = 1; i < N; i++)
    cat[i] = (cat[i] * fct[i]) % mod;
  return;
}

void go() {
  for(int i = 1; i <= 200; i++)
    dp[1][i] = cat1[i];

  for(int i = 2; i <= 200; i++) {
    for(int j =1; j <= 200; j++) {
      for(int k = 1; k <= j; k++) {
        dp[i][j] += (dp[i - 1][j - k] * cat1[k]) % mod;
        dp[i][j] %= mod;
      }
    }
  }
  return;
}

void solve() {
  pre();
  go();
  int t;
  cin >> t;
  while(t--) {
    int X, Y;
    cin >> X >> Y;
    LL ans = 0;
    for(int j = 1; j <= Y; j++) {
      LL add = (dp[j][Y] * ncr(2*X + 1, j)) % mod;
      add = (add * cat[X]) % mod;
      add = (add * fct[Y]) % mod;
      ans = (ans + add) % mod;
    }
    cout << ans << "\n";
  }
  return;
}
int main() {
    ios::sync_with_stdio(false) ; cin.tie(nullptr);
    solve();
    return  0;
}
