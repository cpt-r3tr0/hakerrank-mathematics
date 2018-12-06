#include <iostream>
using namespace std;
const int mod = 1000000007;
int q, n, m, inv[500009];
int main() {
    inv[1] = 1;
    for (int i = 2; i <= 500000; ++i) {
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    }
    cin >> q;
    while (q--) {
        cin >> m >> n;
        int sum = 0, mul = 1;
        for (int i = 0; i <= m - n; ++i) {
            sum = (sum + mul) % mod;
            mul = 1LL * mul * (n - 1) % mod * (m - i) % mod * inv[i + 1] % mod;
        }
        cout << sum << '\n';
    }
    return 0;
}
