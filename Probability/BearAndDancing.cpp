#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>

using namespace std;

typedef long long int64;
typedef pair<int, int> ii;
const int INF = 1 << 30;

const int N = 31;
complex<double> A[N][N][N * N];
bool visit[N][N][N * N];

int n, m;
double p;

complex<double> solve(int x, int y, int z) {

  if (x == n && y == m) return 0.0;
  if (visit[x][y][z]) return A[x][y][z];
  complex<double>& ret = A[x][y][z];
  visit[x][y][z] = true;
  double rx = (double)x / n;
  double ry = (double)y / m;
  double rz = (double)z / (x * y);
  ret = 0.0;
  if (x && y) {
    if (z) {
      ret +=
        rx * ry * rz * p * complex<double>(0, 1) +
        rx * ry * rz * (1 - p);
    }
    if (z != x * y) {
      ret +=
        rx * ry * (1 - rz) * (1.0 + solve(x, y, z + 1));
    }
  }
  if (x && y != m)
    ret += rx * (1 - ry) * (1.0 + solve(x, y + 1, z + 1));
  if (x != n && y)
    ret += (1 - rx) * ry * (1.0 + solve(x + 1, y, z + 1));
  if (x != n && y != m)
    ret += (1 - rx) * (1 - ry) * (1.0 + solve(x + 1, y + 1, z + 1));
  if (x && y)
    ret /= (1 - rx * ry * rz * (1 - p));
  return ret;
}

int main() {
  scanf("%d%d%lf", &n, &m, &p);
  complex<double> x = solve(0, 0, 0);
  printf("%.10f\n", x.real() / (1.0 - x.imag()));
  return 0;
}
