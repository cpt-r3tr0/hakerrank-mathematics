#include <bits/stdc++.h>
using namespace std;
int mod = 1000000000 + 7;
long long f[1000001] = {1};
long long fi[1000001] = {1};

long long pwr(long long a, int b) {
	long long ret = 1;
	while (b) {
		if (b & 1) {
			ret = ret * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return ret;
}

long long C(int n, int r) {
	if (n < r) {
		return 0;
	}
	long long num = f[n];
	long long den = fi[r] * fi[n - r] % mod;
	return num * den % mod;
}

long long solutions(int n, int r, int sub) {
	return C(n + r - 1 - sub, r - 1);
}

int main() {
	for (int i = 1; i <= 1000000; ++i) {
		f[i] = f[i - 1] * i % mod;
		fi[i] = pwr(f[i], mod - 2);
	}
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		long long ans = 0;
		for (int blocks = 1; blocks <= k / 2; ++blocks) {
			ans = (ans + solutions(k, blocks, blocks * 2) * solutions(n - k, blocks + 1, blocks - 1)) % mod;
		}
		cout << ans << endl;
	}
}
