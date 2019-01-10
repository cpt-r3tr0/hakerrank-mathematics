#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <tuple>
#include <stack>
#include <queue>

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i8 = signed char;
using i16 = signed short;
using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;

const int mod = 1e9 + 7;
const int N_MAX = 3e6;

int facts[N_MAX + 1];
int ifacts[N_MAX + 1];
int invs[N_MAX + 1];

void init() {
  invs[0] = invs[1] = 1;
  rep(i, 2, N_MAX + 1) invs[i] = i64(invs[mod % i]) * (mod - mod / i) % mod;
  facts[0] = 1;
  ifacts[0] = 1;
  rep(i, 1, N_MAX + 1) {
    facts[i] = i64(facts[i - 1]) * i % mod;
    ifacts[i] = i64(ifacts[i - 1]) * invs[i] % mod;
  }
}

void solve() {
  init();
  int T; scanf("%d", &T);

  rep(_, T) {
    i64 x, y, z; scanf("%lld %lld %lld", &x, &y, &z);
    if (x > y) swap(x, y);
    y = (y % mod + mod);
    z = (z % mod + mod);
    int yp = y, zf = 1;
    i64 base = 0;
    rep(i, x) {
      base += i64(yp) * ifacts[i + 1] % mod;
      yp = i64(yp) * (y + i + 1) % mod;
    }
    i64 ans = 0;
    int yf = 1, xf = 1;
    rep(i, x) {
      ans += base * zf % mod;
      xf = i64(xf) * (x - i) % mod * invs[i + 1] % mod;
      yf = i64(yf) * (y - i) % mod * invs[i + 1] % mod;
      base = (base + mod - i64(xf) * yf % mod) % mod;
      zf = i64(zf) * (z - 1 - i) % mod * invs[i + 1] % mod;
    }
    printf("%lld\n", ans % mod);
  }
}

int main() {
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
