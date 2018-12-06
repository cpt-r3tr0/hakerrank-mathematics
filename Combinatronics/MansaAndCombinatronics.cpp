#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 99991;

long long pow(long long x, long long n) {
    auto result = 1ll;
    while(n != 0) {
        if(n % 2 == 1) {
            result = result * x % MOD;
        }
        n /= 2;
        x = x * x % MOD;
    }
    return result;
}

long long inverse(long long n) {
    return pow(n, MOD - 2);
}

long long C(long long n, long long k, long long p) {
    auto top = 1ll, bottom = 1ll;
    for(auto i = 1ll; i <= k; i++) {
        top = top * (n + 1 - i) % p;
        bottom = bottom * i % p;
    }
    return top * inverse(bottom) % p;
}

long long C(long long n, long long k) {
    auto result = 1ll;
    while(n > 0) {
        result = (result * C(n % MOD, k % MOD, MOD)) % MOD;
        n /= MOD;
        k /= MOD;
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    for(long long N; cin >> N; ) {
        if(N == 1) {
            cout << 1 << endl;
        } else {
            cout << (C(3 * N, N) - 2 * C(3 * N, N - 1) + C(3 * N, N - 2) + MOD + MOD) % MOD << endl;
        }
    }
    return 0;
}
