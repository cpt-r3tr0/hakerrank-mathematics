#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;

vector<int> PrimeFactors(int n) {
    vector<int> r;
    for (int p = 2; n / p >= p; p = p == 2 ? 3 : p + 2) {
        if (n % p == 0) {
            r.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) r.push_back(n);
    return r;
}

bool Okay(int N, int A, int pow) {
    ll r = 1, u = 2;
    for (int i = 0; pow >> i; ++i) {
        if (pow >> i & 1) r = r * u % N;
        u = u * u % N;
    }
    return A * r % N == A;
}

int Solve(int N, int A) {
    N = N * 2 + 1;
    if (A < 0) A += N;
    // Find k s.t. A * 2**k == A (mod N).
    auto pf = PrimeFactors(N);
    vector<int> all_pf = pf, tmp;
    int phi = N;
    for (int p : pf) {
        phi = phi / p * (p - 1);
        tmp = PrimeFactors(p - 1);
        all_pf.insert(all_pf.end(), tmp.begin(), tmp.end());
    }
    if (!Okay(N, A, phi)) {
        cerr << "Weird: " << N << ' ' << A << ' ' << phi << endl;
    }
    sort(all_pf.begin(), all_pf.end());
    all_pf.erase(unique(all_pf.begin(), all_pf.end()), all_pf.end());
    int ans = phi;
    for (int p : all_pf) {
        while (ans % p == 0 && Okay(N, A, ans / p)) ans /= p;
    }
    return N - 1 - ans;
}

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int T;
    for (cin >> T; T--;) {
        int N, A;
        cin >> N >> A;
        cout << Solve(N, A) << endl;
    }
}
