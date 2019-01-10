
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <cfloat>
#include <climits>
#include <cstring>
#include <cmath>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> i_i;
typedef pair<ll, int> ll_i;
typedef pair<double, int> d_i;
typedef pair<ll, ll> ll_ll;
typedef pair<double, double> d_d;
struct edge { ll B, T, F, P; };

unsigned MOD = 1000000007;
ll _MOD = 1000000009;
double EPS = 1e-10;
int UNKO = INT_MAX;

struct segment_tree_max {
    int n; vector<int> v;
    segment_tree_max(int _n) {
        for (n = 1; n < _n; n *= 2);
        v = vector<int>(n * 2 - 1, INT_MIN);
    }
    void set(int i, int x) {
        int k = i + n - 1;
        v[k] = x;
        while (k > 0) {
            k = (k - 1) / 2;
            v[k] = max(v[k * 2 + 1], v[k * 2 + 2]);
        }
    }
    int _get(int i, int j, int k, int l, int r) {
        if (r <= i || j <= l) return INT_MIN;
        if (i <= l && r <= j) return v[k];
        int vl = _get(i, j, k * 2 + 1, l, (l + r) / 2);
        int vr = _get(i, j, k * 2 + 2, (l + r) / 2, r);
        return max(vl, vr);
    }
    int get(int i, int j) { return _get(i, j, 0, 0, n); }
};

ll f(vector<int>& a, segment_tree_max& st, int l, int r, map<i_i, ll>& memo) {
    if (memo.count(i_i(l, r))) return memo[i_i(l, r)];
    if (r - l == 1) return 1;
    ll sum = 0;
    int x;
    for (x = l + 1; x < r && a[x] <= a[l + 1]; x++);
    int maxi = st.get(x, r);
    for (int m = min(r - 1, x); m >= l + 1; m--) {
        maxi = max(maxi, a[m]);
        if (a[m] == maxi && (r - m) % 2)
            sum = (sum + f(a, st, l + 1, m, memo) * f(a, st, m, r, memo)) % MOD;
    }
    return memo[i_i(l, r)] = sum;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    segment_tree_max st(n);
    for (int i = 0; i < n; i++)
        st.set(i, a[i]);
    map<i_i, ll> memo;
    cout << f(a, st, 0, n, memo) << endl;
}
