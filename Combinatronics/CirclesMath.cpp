#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cassert>
#include <functional>
#include <complex>

using namespace std;
typedef long double LD;
typedef long long LL;

const int kMod = 1000000007;

long long ModPow(long long x, long long deg, long long mod) {
    long long ret = 1;
    while (deg) {
        if (deg & 1) {
            ret = (ret * x) % mod;
        }
        x = (x * x) % mod;
        deg >>= 1;
    }
    return ret;
}

long long fact[1000005];
long long rfact[1000005];
long long dp[1000005][2];

int main()
{
    fact[0] = 1;
    rfact[0] = 1;
    for (int i = 1; i < 1000005; ++i) {
        fact[i] = (fact[i - 1] * i) % kMod;
        rfact[i] = ModPow(fact[i], kMod - 2, kMod);
    }
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n, k;
        cin >> n >> k;
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        long long sum = 0;
        long long sum2 = 0;
        for (int i = 1; i <= n; ++i) {
            if (i >= 2) {
                sum = (sum + dp[i - 2][1] * fact[n + 1 - i]) % kMod;
                sum2 = (sum2 + dp[i - 2][0] * fact[n + 1 - i]) % kMod;
            }
            dp[i][1] = (dp[i][1] + sum * rfact[n - i] % kMod) % kMod;
            if (i - k >= 0) {
                sum2 = (sum2 + kMod - dp[i - k][0] * fact[n - 1 - i + k] % kMod) % kMod;
                dp[i][0] = (dp[i][0] + sum2 * rfact[n - i]) % kMod;
                dp[i][1] = (dp[i][1] + dp[i - k][0] * fact[n - 1 - i + k] % kMod * rfact[n - i]) % kMod;
                sum2 = (sum2 + dp[i - k][0] * fact[n - 1 - i + k]) % kMod;
            } else {
                dp[i][0] = (dp[i][0] + sum2 * rfact[n - i]) % kMod;
            }
        }
        if (k <= 1) {
            dp[n][1] = 0;
        }
        cout << dp[n][1] << "\n";
    }
    return 0;
}
