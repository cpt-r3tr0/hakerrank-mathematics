#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007;

int main() {
    int T;
    for(cin >> T; T > 0; T--) {
        long long L1, R1, L2, R2, L3, R3, L4, R4;
        cin >> L1 >> R1 >> L2 >> R2 >> L3 >> R3 >> L4 >> R4;
        auto result = (R1 - L1 + 1) * (R2 - L2 + 1) % MOD * (R3 - L3 + 1) % MOD * (R4 - L4 + 1) % MOD;
        result = (result - max(min(R1, R2) - max(L1, L2) + 1, 0ll) * (R3 - L3 + 1) % MOD * (R4 - L4 + 1)) % MOD;
        result = (result - max(min(R2, R3) - max(L2, L3) + 1, 0ll) * (R1 - L1 + 1) % MOD * (R4 - L4 + 1)) % MOD;
        result = (result - max(min(R3, R4) - max(L3, L4) + 1, 0ll) * (R1 - L1 + 1) % MOD * (R2 - L2 + 1)) % MOD;
        result = (result - max(min(R1, R4) - max(L1, L4) + 1, 0ll) * (R2 - L2 + 1) % MOD * (R3 - L3 + 1)) % MOD;
        result = (result + max(min({R1, R2, R3}) - max({L1, L2, L3}) + 1, 0ll) * (R4 - L4 + 1)) % MOD;
        result = (result + max(min({R1, R2, R4}) - max({L1, L2, L4}) + 1, 0ll) * (R3 - L3 + 1)) % MOD;
        result = (result + max(min({R2, R3, R4}) - max({L2, L3, L4}) + 1, 0ll) * (R1 - L1 + 1)) % MOD;
        result = (result + max(min({R1, R3, R4}) - max({L1, L3, L4}) + 1, 0ll) * (R2 - L2 + 1)) % MOD;
        result = (result + max(min(R2, R3) - max(L2, L3) + 1, 0ll) * max(min(R1, R4) - max(L1, L4) + 1, 0ll)) % MOD;
        result = (result + max(min(R1, R2) - max(L1, L2) + 1, 0ll) * max(min(R3, R4) - max(L3, L4) + 1, 0ll)) % MOD;
        result = (result - 3 * (max(min({R1, R2, R3, R4}) - max({L1, L2, L3, L4}) + 1, 0ll))) % MOD;
        result = (result + MOD) % MOD;
        cout << result << endl;
    }
    return 0;
}
