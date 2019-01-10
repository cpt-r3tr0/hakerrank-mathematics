#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <unordered_set>
using namespace std;

#define N 210000
#define P 1000000009
vector <int> ve[N];
int pw[N], ni[N];
int dp[51000][5][21];
int g[51000];
int num[21][21];
int n;
int f[21], F, K;

int C(int x, int y) {
    return 1LL * pw[x] * ni[y] % P * ni[x - y] % P;
}

int Pow(int x, int y) {
    int ans = 1;
    for (int i = 1; i <= y; i *= 2, x = 1LL * x *x % P)
        if (i & y)
            ans = 1LL * ans * x % P;
    return ans;
}

void up(int &x, int y) {
    x = (x + y) % P;
}

void dfs(int k) {
    for (int i = 0; i < ve[k].size(); i++)
        dfs(ve[k][i]);

    for (int i = 0; i <= 20; i++)
        for (int j = 0; j < F; j++) {

            for (int p = 1; p <= f[j] && i + p <= K; p++) {
                int cur = 0;

                cur = 1LL * C(K - i, p) * num[j][p] % P;
                // if (!i)
                    // printf("?? %d %d %d %d\n", k, j, p, cur);
                // printf("?? %d %d\n", );
                for (int q = 0; q < (int) ve[k].size(); q++) {
                    // cur = 1LL * cur * ((g[ve[k][q]] - dp[ve[k][q]][j][0]) % P + dp[ve[k][q]][j][p]) % P;
                    // cur =
                    int tmp = 0;
                    for (int tt = 0; tt < F; tt++)
                        if (tt != j)
                            up(tmp, dp[ve[k][q]][tt][p]);
                    cur = 1LL * cur * tmp % P;
                }
                up(dp[k][j][i], cur);
            }

        }
    for (int i = 0; i < F; i++)
        up(g[k], dp[k][i][0]);
}

int calc(int x, int y) {
    if (x == 4) {
        return (11LL * Pow(12, P - 2) % P * Pow(y, 2) % P + 1LL * Pow(12, P - 2) * Pow(y, 4)) % P;
    }else if (x == 6) {
        return (1LL * Pow(3, P - 2) * Pow(y, 2) % P + 1LL * Pow(2, P - 2) * Pow(y, 3) % P + 1LL * Pow(8, P - 2) * Pow(y, 4) % P + 1LL * Pow(24, P - 2) * Pow(y, 6) % P) % P;
    }else if (x == 8) {
        return (1LL * Pow(4, P - 2) * Pow(y, 2) % P + 17LL * Pow(24, P - 2) % P * Pow(y, 4) % P + 1LL * Pow(24, P - 2) * Pow(y, 8)) % P;
    }else if (x == 12) {
        return (11LL * Pow(15, P - 2) % P * Pow(y, 4) % P + 1LL * Pow(4, P - 2) * Pow(y, 6) % P + 1LL * Pow(60, P - 2) * Pow(y, 12)) % P;
    }else {
        return (2LL * Pow(5, P - 2) % P * Pow(y, 4) % P + 1LL * Pow(3, P - 2) * Pow(y, 8) % P + 1LL * Pow(4, P - 2) * Pow(y, 10) % P + 1LL * Pow(60, P - 2) * Pow(y, 20) % P) % P;
    }
}

int main() {
    scanf("%d%d%d", &n, &K, &F);
    for (int i = 0; i < F; i++)
        scanf("%d", &f[i]);
    pw[0] = 1;
    for (int i = 1; i <= 200000; i++)
        pw[i] = 1LL * pw[i - 1] * i % P;
    for (int i = 0; i <= 200000; i++)
        ni[i] = Pow(pw[i], P - 2);

    // printf("%d %d %d\n", calc(20, 1), calc(20, 2), calc(20, 3));
    for (int i = 0; i < F; i++) {
        num[i][1] = 1;
        for (int j = 2; j <= f[i]; j++) {
            int x = calc(f[i], j);
            num[i][j] = x;
            for (int p = 1; p < j; p++)
                up(num[i][j], -1LL * C(j, p) * num[i][p] % P);
            // printf("xx %d %d %d\n", f[i], j, num[i][j]);
        }
    }

    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        ve[x].push_back(i);
    }
    dfs(1);

    printf("%d\n", (g[1] + P) % P);
}
