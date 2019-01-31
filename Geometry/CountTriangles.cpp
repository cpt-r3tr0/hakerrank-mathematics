#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <queue>
#include <ctime>
#pragma comment(linker, "/STACK:256000000")

using namespace std;

const int maxN = 11000;

int get_total(int a, int b, int c) {
  int n = a + b + c;
  if (a == b && b == c) {
    return n / 3;
  }
  if (a == b) {
    return n;
  }
  if (b == c) {
    return n;
  }
  return 2 * n;
}

void order(int& a, int& b, int& c) {
  if (a > b) swap(a, b);
  if (a > c) swap(a, c);
  if (b > c) swap(b, c);
}

long long total[maxN];

long long total_equal(int n) {
  if (n == 3) {
    return 0;
  }
  if (n == 4) {
    return 6;
  }

  long long partitions = total[n];

  int equalsides = 0;
  for (int i = 1; 2 * i < n; ++i) {
    ++equalsides;
  }
  partitions -= equalsides;

  long long cn = 2 * n;
  long long value = (cn * (cn - 1)) / 2;
  long long result = partitions * value;

  for (int i = 1; 2 * i < n; ++i) {
    int rest = n - 2 * i;
    int a = i, b = i, c = n - 2 * i;
    order(a, b, c);
    long long cn = get_total(a, b, c);
    result += (cn * (cn - 1)) / 2;
  }

  if (n % 4 == 0) {
    for (int a = 1; a < n / 4; ++a) {
      int b = n / 4 - a;
      if (a >= b) {
        break;
      }

      int na1 = a, nb1 = 2 * b, nc1 = n - na1 - nb1;
      int na2 = b, nb2 = 2 * a, nc2 = n - na2 - nb2;
      order(na1, nb1, nc1);
      order(na2, nb2, nc2);

      result += get_total(na1, nb1, nc1) * get_total(na2, nb2, nc2);
    }
  }

  if (n % 24 == 0) {
    result += 4LL * n * n;
  }
  if (n % 30 == 0) {
    result += 8LL * n * n;
  }
  return result;
}

long long solve(int n, const string& s) {
  vector <int> unused;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '0') {
      unused.push_back(i);
    }
  }

  long long result = total_equal(n);

  map<pair<int, int>, int> lengths;

  for (int i = 0; i < unused.size(); ++i) {
    for (int j = i + 1; j < unused.size(); ++j) {
      for (int k = j + 1; k < unused.size(); ++k) {
        int a = unused[j] - unused[i];
        int b = unused[k] - unused[j];
        int c = n - a - b;
        order(a, b, c);
        ++lengths[make_pair(a, b)];
      }
    }
  }

  long long inpart = 0;

  for (map<pair<int, int>, int>::iterator it = lengths.begin(); it != lengths.end(); ++it) {
    int a = it->first.first;
    int b = it->first.second;
    int c = n - a - b;
    int ctotal = it->second;
    result -= (ctotal * (ctotal - 1)) / 2;

    int totaltype = get_total(a, b, c) - ctotal;

    if (n % 4 == 0) {
      if (b % 2 == 0) {
        int na = 2 * a, nb = b / 2, nc = n - na - nb;
        if (nc > 0) {
          if (a + b / 2 == n / 4) {
            order(na, nb, nc);
            if (!(na == a && nb == b)) {
              totaltype += get_total(na, nb, nc);
              if (lengths.count(make_pair(na, nb))) {
                totaltype -= lengths[make_pair(na, nb)];
                inpart += ctotal * lengths[make_pair(na, nb)];
              }
            }
          }
        }
      }
      if (a % 2 == 0 && a != b) {
        int na = a / 2, nb = 2 * b, nc = n - na - nb;
        if (nc > 0) {
          if (b + a / 2 == n / 4) {
            order(na, nb, nc);
            if (!(na == a && nb == b)) {
              totaltype += get_total(na, nb, nc);
              if (lengths.count(make_pair(na, nb))) {
                totaltype -= lengths[make_pair(na, nb)];
                inpart += ctotal * lengths[make_pair(na, nb)];
              }
            }
          }
        }
      }
    }

    if (n % 24 == 0) {
      int k = n / 24;
      if (a % k == 0 && b % k == 0 && c % k == 0) {
        int na = a / k, nb = b / k, nc = c / k;

        if (na == 3 && nb == 6 && nc == 15) {
          int ua = 2 * k, ub = 10 * k, uc = 12 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }

        if (na == 2 && nb == 10 && nc == 12) {
          int ua = 3 * k, ub = 6 * k, uc = 15 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }
      }
    }

    if (n % 30 == 0) {
      int k = n / 30;
      if (a % k == 0 && b % k == 0 && c % k == 0) {
        int na = a / k, nb = b / k, nc = c / k;

        if (na == 1 && nb == 11 && nc == 18) {
          int ua = 2 * k, ub = 6 * k, uc = 22 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }

        if (na == 2 && nb == 6 && nc == 22) {
          int ua = 1 * k, ub = 11 * k, uc = 18 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }

        if (na == 4 && nb == 12 && nc == 14) {
          int ua = 6 * k, ub = 7 * k, uc = 17 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }

        if (na == 6 && nb == 7 && nc == 17) {
          int ua = 4 * k, ub = 12 * k, uc = 14 * k;
          totaltype += get_total(ua, ub, uc);
          if (lengths.count(make_pair(ua, ub))) {
            totaltype -= lengths[make_pair(ua, ub)];
            inpart += ctotal * lengths[make_pair(ua, ub)];
          }
        }
      }
    }
    result -= ctotal * totaltype;
  }
  result -= inpart / 2;
  return result;
}

void solve_test() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  long long res = solve(n, s);
  cout << res << endl;
}

long long get_n(int n) {
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j + i <= n && j <= n - i - j; ++j) {
      ++res;
    }
  }
  return res;
}

void precalc() {
  for (int i = 0; i < 10; ++i) {
    total[i] = get_n(i);
  }
  for (int i = 10; i < maxN; ++i) {
    total[i] = 1 + total[i - 2] + total[i - 3] - total[i - 5];
  }
}

int main() {
  precalc();

  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve_test();
  }

  return 0;
}
