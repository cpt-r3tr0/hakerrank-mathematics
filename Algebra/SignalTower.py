#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <complex>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;

namespace SignalTower {
typedef long long ll;
const unsigned int buffer_size = 1 << 16;
char input_buffer[buffer_size];
unsigned int bytes_read = 0;
unsigned int input_index = 0;

inline char next_char() {
  if (input_index == bytes_read) {
    bytes_read = fread(input_buffer, sizeof(char), buffer_size, stdin);
    input_buffer[bytes_read] = '\0'; //sentinel
    input_index = 0;
  }
  return input_buffer[input_index++];
}

inline int next_int() {
  char c = 0;
  int ans = 0;
  while (c < '-')
    c = next_char();
  bool neg;
  if (c == '-')
    neg = true, c = next_char();
  else
    neg = false;
  for (; c >= '0'; c = next_char())
    ans = (ans << 1) + (ans << 3) + c - '0';
  return neg ? -ans : ans;
}

char output_buffer[buffer_size];
unsigned int output_index = 0;

inline void write_flush() {
  fwrite(output_buffer, sizeof(char), output_index, stdout);
  output_index = 0;
}

inline void write_char(char c) {
  output_buffer[output_index++] = c;
  if (output_index == buffer_size)
    write_flush();
}

inline void write_ll(ll num) {
  if (num >= 10)
    write_ll(num / 10);
  write_char(num % 10 + '0');
}

struct Node {
  ll* sum;
  int* val, len;
};

struct MedNode {
  int* pos, len;
};

#ifdef AZN
#define MAX (1 << 8)
#else
#define MAX (1 << 18)
#endif
#define INF 2000000000LL
int x[MAX], y[MAX], order[MAX];
Node xtree[MAX], ytree[MAX];
Node* qnodes[2][30];
MedNode xmtree[MAX], ymtree[MAX];
int N, Q, PW, qcnt;

ll go_slow(int* v, int l, int r) {
  static int temp[100111];
  int m = 0, med;
  ll res = 0;
  for (int i = l; i <= r; i++)
    temp[m++] = v[i];
  nth_element(temp, temp + (m >> 1), temp + m);
  med = temp[m >> 1];
  for (int i = 0; i < m; i++)
    res += abs(temp[i] - med);
  return res;
}

void combine(Node& t, Node& l, Node& r) {
  static ll temp[MAX];
  t.len = l.len + r.len;
  t.val = new int[t.len];
  t.sum = new ll[t.len + 1];
  merge(l.val, l.val + l.len, r.val, r.val + r.len, t.val);
  for (int i = 1; i <= t.len; i++)
    t.sum[i] = t.sum[i - 1] + INF - t.val[i - 1];
  temp[t.len] = 0;
  for (int i = t.len - 1; i >= 0; i--) {
    temp[i] = temp[i + 1] + t.val[i] + INF;
    t.sum[i] += temp[i];
  }
}

void build(Node* tree, int* arr) {
  for (int i = PW; i < N + PW; i++) {
    tree[i].len = 1;
    tree[i].val = new int[1];
    tree[i].val[0] = arr[i - PW];
    tree[i].sum = new ll[2];
    tree[i].sum[0] = arr[i - PW] + INF;
    tree[i].sum[1] = INF - arr[i - PW];
  }
  for (int i = PW - 1; i > 0; i--)
    combine(tree[i], tree[i << 1], tree[i << 1 | 1]);
}

bool cmpx(int a, int b) {
  return x[a] < x[b] || (x[a] == x[b] && a < b);
}

bool cmpy(int a, int b) {
  return y[a] < y[b] || (y[a] == y[b] && a < b);
}

template <class Comp> void build_med(MedNode* tree, int node, int* par, int len, Comp cmp) {
  tree[node].len = len;
  tree[node].pos = new int[len];
  for (int i = 0; i < len; i++)
    tree[node].pos[i] = par[i];
  if (len == 1)
    return;
  int mid = len >> 1, *arr = tree[node].pos;
  nth_element(arr, arr + mid, arr + len, cmp);
  sort(arr, arr + mid);
  sort(arr + mid, arr + len);
  build_med(tree, node << 1, arr, mid, cmp);
  build_med(tree, node << 1 | 1, arr + mid, len - mid, cmp);
}

void get_nodes(int l, int r) {
  qcnt = 0;
  for (l += PW, r += PW + 1; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      qnodes[0][qcnt] = xtree + l;
      qnodes[1][qcnt++] = ytree + (l++);
    }
    if (r & 1) {
      qnodes[0][qcnt] = xtree + (--r);
      qnodes[1][qcnt++] = ytree + r;
    }
  }
}

ll get_sum(Node& n, int x) {
  static int pos;
  static ll sum;
  pos = upper_bound(n.val, n.val + n.len, x) - n.val;
  sum = n.sum[pos] - pos * (INF - x) - (n.len - pos) * (x + INF);
  return sum;
}

int get_median(MedNode* tree, int node, int l, int r, int rank) {
  while (true) {
    if (tree[node].len == 1)
      return tree[node].pos[0];
    int* pos = tree[node].pos, mid = tree[node].len >> 1;
    int cnt = upper_bound(pos, pos + mid, r) - lower_bound(pos, pos + mid, l);
    if (rank <= cnt)
      node <<= 1;
    else {
      node = node << 1 | 1;
      rank -= cnt;
    }
  }
  return -1;
}

ll go(Node* nodes[30], MedNode* tree, int* arr, int l, int r) {
  ll res = 0;
  int median, i;
  median = get_median(tree, 1, l, r, (r - l + 1) / 2 + 1);
  median = arr[median];
  //pln(median);
  for (i = 0; i < qcnt; i++)
    res += get_sum(*nodes[i], median);
  return res;
}

void solve(int test_num) {
  //scanf("%d %d", &N, &Q);
  N = next_int();
  Q = next_int();
  for (int i = 0; i < N; i++)
    x[i] = next_int();
  for (int i = 0, b; i < N; i++) {
    b = next_int();
    y[i] = x[i] - b;
    x[i] = x[i] + b;
    order[i] = i;
  }
  for (PW = 1; PW < N;)
    PW <<= 1;
  build(xtree, x);
  build(ytree, y);
  build_med(xmtree, 1, order, N, cmpx);
  build_med(ymtree, 1, order, N, cmpy);
//  plnarr(x, x + N);
//  plnarr(xtree[1].val, xtree[1].val + xtree[1].len);
//  plnarr(xtree[1].sum, xtree[1].sum + xtree[1].len + 1);
//  plnarr(y, y + N);
//  plnarr(ytree[1].val, ytree[1].val + ytree[1].len);
//  plnarr(ytree[1].sum, ytree[1].sum + ytree[1].len + 1);
  ll res;
  for (int q = 0, l, r; q < Q; q++) {
    l = next_int() - 1;
    r = next_int() - 1;
    get_nodes(l, r);
    res = go(qnodes[0], xmtree, x, l, r);
    res += go(qnodes[1], ymtree, y, l, r);
    write_ll(res >> 1);
    if (res & 1) {
      write_char('.');
      write_char('5');
    }
    write_char('\n');
    //printf("%.4lf\n", res / 2.0);
  }
  write_flush();
}

void solve() {
  solve(1);
}
}

int main() {
  SignalTower::solve();
  return 0;
}
