#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long MOD = 1000000007;
long N = 200000;
int K = 60; // ceil(log2(10^18))

std::vector<long> f;
std::vector<std::vector<long>> g;

void pre() {
    f.resize(N+1);
    f[0] = 1;
    f[1] = 1;
    for (size_t i = 2; i <= N; i++) {
        f[i] = f[i-1] * i % MOD;
    }
    g.resize(N+1);
    g[1].resize(2);
    g[1][1] = 1;
    g[2].resize(3);
    g[2][1] = 1;
    for (size_t i = 3; i <= N; i++) {
        int e = i < K ? i : K;
        g[i].resize(e+1);
        g[i][0] = 0;
        for (size_t j = 1; j <= e; j++) {
            g[i][j] = ((i-2) * (j < g[i-1].size() ? g[i-1][j] : 0) + g[i-1][j-1]) % MOD;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    pre();
    long T, N, L, R;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        std::cin >> N >> L >> R;
        long r = 0;
        if (N == 1) {
            if (L <= 1 && 1 <= R) {
                r = 1;
            }
        } else {
            if (L <=0 && 0 <= R) {
                r = (r + (N-1) * f[N-1]) % MOD;
            }
            for (unsigned j = 1; j < 60; j++) {
                long n = 1L << j;
                if (n > R || j >= g[N].size()) break;
                if (L <= n && n <= R)
                    r = (r + g[N][j]) % MOD;
            }
            if (r < 0) r += MOD;
        }
        std::cout << r << "\n";
    }
    return 0;
}
